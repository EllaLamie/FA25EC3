//
// Created by Manju Muralidharan on 11/22/25.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "tree.h"
using namespace std;

/*
   Students:
   You will complete the Tree template class.
   main.cpp already:
   1. Runs curl to fetch a story from OpenAI.
   2. Saves output to story.txt.
   3. Parses story.txt into structured nodes.
   4. Calls your Tree methods to build a dynamic tree.

   You must NOT modify this file.
*/

// Structure for raw parsed nodes
struct StoryNodeRaw {
    string id;
    string text;
    vector<string> children;
};

// Step 1. Call OpenAI with curl
string runCurlToOpenAI(const string &apiKey) {
    // Gets the URL for the curl command, finds the content type with header,
    // then inserts API key, and sends the data with model and input
    string command =
        "curl https://api.openai.com/v1/responses "
        "-H \"Content-Type: application/json\" "
        "-H \"Authorization: Bearer " + apiKey + "\" "
        "-d '{"
        "\"model\": \"gpt-4.1-mini\","
     "\"input\": \"Generate a choose-your-own-adventure story as a structured list of nodes. "
     "Each node must have: NODE_ID, NODE_TEXT, CHILD_IDS as a comma-separated list. "
     "Limit to 2 nodes. The format must be strictly: "
     "[NODE_ID] TEXT: ... NEXT: child1, child2, ... "
     "No extra commentary.\""
     "}' "
     " > story.txt";

    cout << "Fetching story from OpenAI..." << endl;
    system(command.c_str());
    return "story.txt"; }

// Step 2. Parse the story file
vector<StoryNodeRaw> parseStoryFile(const string &filename) {
    // Fin is the file reader and the nodes will store all nodes
    ifstream fin(filename);
    vector<StoryNodeRaw> nodes;

    // Make sure the file was able to be opened before continuing
    if (!fin.is_open()) {
        cerr << "Could not open story file." << endl;
        return nodes;
    }

    // Read the file line by line
    string line;
    while (getline(fin, line)) {
        // Make sure we skip any empty lines
        if (line.empty()) continue;

        // Create an object from the structure at the top
        StoryNodeRaw node;

        // Find the start and end of the node ID by finding the brackets
        size_t idStart = line.find('[');
        size_t idEnd = line.find(']');

        // If either of the brackets are missing, skip everything else
        // for this node
        if (idStart == string::npos || idEnd == string::npos) continue;

        // Find the id of the node
        node.id = line.substr(idStart + 1, idEnd - idStart - 1);

        // Find TEXT and NEXT for the node
        size_t textPos = line.find("TEXT:");
        size_t nextPos = line.find("NEXT:");

        // If either are missing, skip everything else and move on
        if (textPos == string::npos || nextPos == string::npos) continue;

        // Find the text for the node using the substring, and skipping "TEXT:" which is
        // 5 characters. Also going until we see NEXT
        string textPart = line.substr(textPos + 5, nextPos - (textPos + 5));

        // Assign the text of the node to what we just found as textPart
        node.text = textPart;

        // Find everything after "NEXT:"
        string nextPart = line.substr(nextPos + 5);

        // Create a stringstream from NEXT
        stringstream ss(nextPart);
        string temp;

        // Use a delimiter to split the children by their commas in between
        while (getline(ss, temp, ',')) {
            // Erase any extra spaces before a node ID
            while (!temp.empty() && temp.front() == ' ') temp.erase(0, 1);
            // This will store the node's children who are not empty
            if (!temp.empty()) node.children.push_back(temp);
        }
        // Now storing the node in a different vector
        nodes.push_back(node);
    }

    // Finally returning all the nodes
    return nodes;
}
// Main Program
int main() {
    // User input to get API key
    cout << "Enter your OpenAI API key: ";
    string apiKey;
    getline(cin, apiKey);

    // Gets the filename by calling runCurlToOpenAI
    string filename = runCurlToOpenAI(apiKey);

    // Open the file as an input file stream
    ifstream fin(filename);

    // This reads the JSON into one string by using iterators from beginning to end
    string json((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    // Finds the part of the JSON that says "output" because my original file looked like this:
    // "output" { "text": ..... }
    size_t outputPos = json.find("\"output\"");
    // Make sure "output" exists
    if (outputPos != string::npos) {

        // If so, the goal is to find "text" that comes after, because that is where the node will
        // be on the original story.txt (as said before, it goes like this: "output" { "text": ..... })
        size_t textPos = json.find("\"text\":", outputPos);
        // Now make sure "text" exists
        if (textPos != string::npos) {
            // Find the first quotation mark of where the nodes are stored because they are stored in one
            // long string. The reason we do textPos + 7 is that "text": is 7 total characters long, if you
            // count the quotation marks and the colon. Basically, we will start after "text" is done and then
            // try to find where the first quotation marks that marks the start of the story
            size_t firstQuote = json.find("\"", textPos + 7);
            // Now we try to find the quotation that ends the story. We will start from the position of the first
            // quote + 1 because we don't want to double count the first quote as the first and last quote. Starting
            // after the first quote will allow us to find the actual ending quote
            size_t secondQuote = json.find("\"", firstQuote + 1);

            // We also have to make sure that the first and second quote exist
            if (firstQuote != string::npos && secondQuote != string::npos) {
                // If the first and second quotes exist like we think they are going to, we simply find the substring
                // so that way we have the entire story in one variable called story. However, we do not include
                // the first and last quotes in the substring because all we want is the story. The quotes were just the
                // things that showed us where the story was in the whole mess of things that were in story.txt
                string story = json.substr(firstQuote + 1,secondQuote - firstQuote - 1);

                // Begin a size_t (unsigned integer type) and set it equal to 0. This is because the type returned by
                // string's method find is usually size_t. Also the above parseStoryFile used size_t for these types of
                // variables
                size_t pos = 0;

                // While loop that looks for where the strong contains \n characters, and then replaces those characters
                // with actual newlines. The reason for the 2 is that \n is 2 characters and the replace function needs to
                // know how many positions from pos will be needed
                while ((pos = story.find("\\n")) != string::npos) {
                    story.replace(pos, 2, "\n");
                }

                // Reset pos to 0 to begin next while loop iteration
                pos = 0;
                // This is like an extra while loop check because every text in the story.txt file starts with [number].
                // This loop then finds every place where the beginning of each node is by searching for the opening bracket
                while ((pos = story.find("[", pos)) != string::npos) {
                    // Check if the beginning of a new node does not begin on a new line
                    if (pos > 0 && story[pos - 1] != '\n') {
                        // If it does not, then insert a new line there
                        story.insert(pos, "\n");
                        // Then increase pos because we just added a new character
                        pos++;
                    }
                    // Increase pos for next time so we don't end up continuing to look at the same bracket
                    pos++;
                }

                // Write the cleaned story over whatever was in story.txt before
                ofstream fout(filename, ios::trunc);
                fout << story;
            }
        }
    }

    // Create the nodes using parseStoryFile method
    vector<StoryNodeRaw> rawNodes = parseStoryFile(filename);

    // Check if there are no nodes
    if (rawNodes.empty()) {
        cerr << "Story was empty or invalid." << endl;
        return 1;
    }


    // Create a tree for the choose your adventure
    Tree<string> adventureTree;

    // TODO: Students, create the root from rawNodes[0]
     adventureTree.createRoot(rawNodes[0].id, rawNodes[0].text);

    // TODO: Students, add all remaining nodes
    // Iterate through all the rawNodes
    for (int i = 0; i < rawNodes.size(); i++) {
        // First find the parentID
        string parentID = rawNodes[i].id;
        // For each child in the collection of rawNode's children
        for (string childID : rawNodes[i].children) {
            // At first, childText is empty
            string childText = "";
            // Use a lambda to trim leading spaces
            auto trimLambda = [](const string &s) {
                // Tries to find the first character that is not a space, tab, return, or newline.
                // Set first as that character
                size_t first = s.find_first_not_of(" \t\r\n");
                // See if that character is not found. This means that the string has whitespace only
                // because it does not have any characters not of the set of tabs, spaces, and newlines.
                if (first == string::npos) {
                    return string("");
                }
                // Do the same thing to find the last character that is not a space, tab, return, or newline.
                size_t last = s.find_last_not_of(" \t\r\n");
                // Now you return the substring that starts with first (i.e. the first character that is not
                // some sort of whitespace), and then goes until the last index, which is last - first + 1
                return s.substr(first, last - first + 1);

                };
            // Now iterate through rawNodes again to find the ID that matches with the childID
            for (int j = 0; j < rawNodes.size(); j++) {
                // If the ID's of the current node and the child node match, set the childText to that of the current node
                if (trimLambda(rawNodes[j].id) == trimLambda(childID)) {
                    childText = rawNodes[j].text;
                    break;
                }
            }
            // Now add that node to the tree
            adventureTree.addNode(trimLambda(parentID), trimLambda(childID), childText);
        }
    }

    // TODO: Students, implement a method in Tree<T> called playGame()
    // This method should:
    // 1. Start at the root node.
    // 2. Display the current node's text.
    // 3. Display numbered options for each child.
    // 4. Ask the user which path to take.
    // 5. Move to the selected child and continue until a node has no children.
    // 6. Print an ending message.
    //
    // Example call after tree construction:
    // adventureTree.playGame();

    cout << "Story loaded into your dynamic tree structure." << endl;
    cout << "Implement the Tree class to enable traversal and printing." << endl;

    // TODO: Once implemented, uncomment to allow full gameplay.
     adventureTree.playGame();
    return 0;
}
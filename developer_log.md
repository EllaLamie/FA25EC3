# Developer Log

This is my developer log which includes:
- A dated entry every time you work on the assignment
- A description of what you worked on
- Any bugs, issues, or problems you encountered
- How you attempted to solve each issue
- A brief explanation of every commit you make
- A list of all files modified during each commit

# Dated entries every time I worked on the assignment

November 26, 2025:
Finished Node constructor, tree constructor, createRoot, addNode, and findNode in tree.h

November 27, 2025:
Finished printAll and tree destructor in tree.h class

November 28, 2025:
Finished all other methods, including playGame in tree.h and also everything in main

November 29, 2025:
Was having trouble with the output because it would output empty entries for each number. It would
look like this:
Choose your next action:
1:
2:
I tried adding some extra edge cases to addNode, including making sure that a child was being created
at the right time and was not being created twice, but this did not do anything

November 30, 2025:
Was still having trouble with the empty next choices and finally began realizing that it had to do with 
the story.txt file. Tried to add an extra for loop that would check if the node had empty text, but
this was not the problem and ended up not making any difference. 

December 2, 2025:
Figured out that the problem was that the /n characters were not being treated as actual newline characters
in story.txt, so I tried to implement a delimiter loop that would split each node by the /n characters. 
However, my story.txt still did not look like how it was supposed to look in the README.

December 3, 2025:
Realized that the format was to have each node on a newline, so instead of what I tried to do before, I
decided to actually turn each of the /n characters into actual newlines. That was when my story.txt began
looking normal. It seemed to work fine at that point, and I began testing with Open AI and also changing
the line:
   string filename = runCurlToOpenAI(apiKey);
in main.cpp to:
   string filename = "story.txt";
to test with my own story. This allowed me to see if my program was working correctly with what it was given.

December 4, 2025:
Now the problem became that if there was an input looking like this:

[1] TEXT: You wake up in a mysterious forest with two paths ahead. One path leads deeper into the woods, the other towards a strange glowing cave. Which do you choose? NEXT: 2, 3  
[2] TEXT: You venture deeper into the woods and find an abandoned cabin. Do you enter or keep walking? NEXT: END, END  
[3] TEXT: You approach the glowing cave and hear whispers from within. Do you enter the cave or run away? NEXT: END, END

only the second node would print as the first node's child. The third one would not print at all. I spent a lot of time
trying to figure this out and ended up adding a trim function because I thought the problem was with extra spaces. This 
did turn out to be the case, and now it is working totally fine! 

December 5, 2025:
Now I ran into an infinite loop problem where there would be some times where each node in the input would point to each other
so I added an extra check in playGame by using a vector called visited and adding nodes to visited once they had been visited.

December 6, 2025:
Created the developer log and am finalizing comments and doing some extra testing. Then I will make my final commit.

December 7, 2025:
Tried to figure out where to put the story.txt

December 8, 2025:
Checked everything one last time

# All commits

November 26, 2025:
Finished Node constructor, tree constructor, createRoot, addNode, and findNode in tree.h

   Files Modified:
   tree.h

   Reasoning Behind Commit:
   Wanted to show incremental work, because that day I only worked on the 5 methods (including two contructors)
   in tree.h

November 27, 2025:
Finished printAll and tree destructor in tree.h class

   Files Modified:
   tree.h

   Reasoning Behind Commit:
   Wanted to show that I had finished every method in the tree class (besides the playGame method)

November 28, 2025:
Finished playGame and every TODO in main

   Files Modified:
   tree.h
   main.cpp

   Reasoning Behind Commit:
   Wanted to commit to show that I had finished all methods and TODOs.

December 6, 2025:
Created and wrote most of the developer log

   Files Modified:
   developer_log.md

   Reasoning Behind Commit:
   Wanted to make sure the developer log development was in github

December 7, 2025:
Finished all debugging. Everything seemed to be working

   Files Modified:
   tree.h
   main.cpp

   Reasoning Behind Commit:
   Had already finished all the methods and TODOs in the last commit, wanted this commit to
   represent the debugging process. Now you can see side by side the changes I had to make
   after I had finished everything.

December 8, 2025:
Added to the developer log and created the story.txt so had to commit one last time

   Files Modified:
   developer_log.md
   story.txt

   Reasoning Behind Commit:
   Was planning on submitting so I needed to finalize everything in git hub.

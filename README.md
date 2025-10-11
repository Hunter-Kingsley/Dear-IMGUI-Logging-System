For this logger I needed to make the class a singleton, so I created a method that initializes the static instance as a pointer that can be referenced anywhere.

The logger class holds a list of log structs that contain all the information the log needs. Each frame, the log list is looped over to construct the strings before being printed.

I asked Graeme whether or not to use the "LogToFile" ImGui function, and he said to just do it the old-fashioned way. So every time a log is created, the string is outputted to the file "logs.txt." The stream for the file is created in the constructor and closed in the destructor, so you won't see the output to the file until you stop running the program. 

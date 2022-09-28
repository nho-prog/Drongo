# Introduction
  This project involves developing an Enterprise Service Bus (ESB) in C. It is assumed that you are comfortable programming in C on a *NIX type of operating system. We will be using git to version control our source code artefacts
 ##Setting up the development environment
   Following instructions assume that you are working on an Ubuntu machine, and are in the sudoers group (or have root access).
   ###Required tools
  1. An IDE. You should use either https://code.visualstudio.com or https://www.jetbrains.com/clion/ for writing and debugging your code.
  2.Postman for easily testing the HTTP endpoints.
  3.git for working with version control repositories. You can install the git client by running sudo apt install git in a shell.
  
  ###Installing essential libraries that you will need
 1. Open a shell and run sudo apt update
 2.Ensure that you have installed the essential headers and libraries: sudo apt install build-essential
 4.You can write unit tests for all your C code using munit. NOTE: We will start with writing the unit tests via simple hand-crafter test functions, and then later move to something like munit.
 5.Install Kore Web framework as  describe here https://docs.kore.io/4.1.0/install.html. You will use it to write an HTTP endpoint for receiving the requests for the ESB. NOTE: A skeleton is provided to get you started. However, you are strongly encouraged to go through the Kore's simple guide.

Multithreaded HTTP Web Server in C

This project implements a lightweight multithreaded HTTP web server in C using TCP socket programming. The server is capable of handling multiple client requests concurrently using a thread pool architecture. It parses HTTP requests, serves static files from a local directory, determines appropriate MIME types, and logs incoming requests. The goal of this project is to demonstrate core concepts from Operating Systems, Computer Networks, and Systems Programming by building a basic but functional web server from scratch.

Key Features

TCP socket based HTTP server
Multithreaded request handling using a thread pool
Task queue to manage incoming client connections
Basic HTTP request parsing
Static file serving from a www directory
MIME type detection for different file types
Request logging system
Custom 404 error page

Project Structure
src/ – Contains the main server implementation files
include/ – Header files for server and thread pool modules
www/ – Static files served by the web server (HTML, CSS, JS, images)
logs/ – Stores server request logs
README.md – Project documentation

Technologies Used
C Programming
TCP Socket Programming
Multithreading
HTTP Protocol
File I/O

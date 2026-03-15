# Multithreaded HTTP Web Server in C

<p>This project implements a lightweight multithreaded HTTP web server in C using TCP socket programming. The server is capable of handling multiple client requests concurrently using a thread pool architecture. It parses HTTP requests, serves static files from a local directory, determines appropriate MIME types, and logs incoming requests. The goal of this project is to demonstrate core concepts from Operating Systems, Computer Networks, and Systems Programming by building a basic but functional web server from scratch.</p>

Key Features

TCP socket based HTTP server<br>
Multithreaded request handling using a thread pool<br>
Task queue to manage incoming client connections<br>
Basic HTTP request parsing<br>
Static file serving from a www directory<br>
MIME type detection for different file types<br>
Request logging system<br>
Custom 404 error page<br>

Project Structure

src/ – Contains the main server implementation files<br>
include/ – Header files for server and thread pool modules<br>
www/ – Static files served by the web server (HTML, CSS, JS, images)<br>
logs/ – Stores server request logs<br>
README.md – Project documentation<br>


Technologies Used

C Programming<br>
TCP Socket Programming<br>
Multithreading<br>
HTTP Protocol<br>
File I/O

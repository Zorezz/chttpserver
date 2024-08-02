# CHTTPServer
This repository is a HTTP server written in pure C it is only meant for my own learning of HTTP requests and replies. It it not meant for production use.

# Building
```
gcc main.c -o server

```

# TODO
This repository is a heavy WIP it currently only supports a GET request for specifically the root "/" and sends the index.html file. The code is also very ugly and will be refactored once basic functionality is reached.

- [ ] Add support for multi-threading by spawning a new pthread for each incoming request.
- [ ] Support usage of HTTP status codes such as 401, 404, 501, etc.
- [ ] Refactor the code to make it readable.

<p align="center">
  <img src="https://static.wikia.nocookie.net/logopedia/images/a/a5/MSN_Messenger_2000_%28Icon%29.png/revision/latest?cb=20230101195823" width=200 alt="msn-logo" />
</p>
<h3 align="center">ft_irc</h3>

<p align="center">
  Creating our own Internet Relay Chat service.
  <br />
  <br />
  <img src="https://img.shields.io/badge/c_98%2B-A8B9CC?style=for-the-badge&logo=c&logoColor=white" alt="c98+" />
  <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white" alt="cmake" />
</p>

---
## Table of contents 
- [About](#about)
- [Run](#Run)
- [Goals](#Goals)
- [Ressources](#ressources)

## About <a name="about"></a>

The IRC (Internet Relay Chat) protocol is for use with text based conferencing; the simplest client being any socket program capable of connecting to the server.

## Run <a name="Run"></a>

To use this IRC, you need to have [irssi](https://irssi.org/) installed.
<br />
You should run this command in irssi:

```shell
/CONNECT localhost [PORT] [PASSWORD] [NAME]
```

## Goals <a name="Goals"></a>

### General Setup and Planning
- [X] Create a project repository on GitHub.
- [X] Define project requirements and objectives.
- [X] Set up a development environment.
- [ ] Create an initial project structure.

### Server Implementation
- [ ] Design and implement the IRC server architecture.
- [ ] Implement server connection and socket handling.
- [ ] Define and handle IRC commands and messages.
- [ ] Manage user registration and authentication.
- [ ] Develop channel management features.

### Client Implementation
- [ ] Design and implement the IRC client user interface.
- [ ] Implement client connection and socket handling.
- [ ] Handle user input and send IRC commands.
- [ ] Display messages and updates from the server.

### Communication Protocol
- [ ] Define and document the IRC communication protocol.
- [ ] Ensure proper encoding and decoding of IRC messages.

### Testing and Quality Assurance
- [ ] Write unit tests for server and client components.
- [ ] Perform integration testing to ensure proper communication.
- [ ] Address and resolve any bugs or issues.
- [ ] Conduct code reviews for code quality.

### Additional Features (Optional)
- [ ] Implement user authentication and registration.
- [ ] Add support for private messages (PMs).
- [ ] Incorporate user roles and permissions.

### Deployment and Scaling (Optional)
- [ ] Prepare the project for deployment.
- [ ] Consider scalability and performance optimizations.

### Celebrate
- [ ] 🥳


## Ressources <a name="ressources"></a>
- RFC 1459: https://datatracker.ietf.org/doc/html/rfc1459#page-7
- Commands : https://muddy-tadpole-89a.notion.site/3d9eb38a40d04fec8888c138c32a4ff3?v=5f5a0a1c611a4eaea5c9c33f05aeba51&pvs=4

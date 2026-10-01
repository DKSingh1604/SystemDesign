# System Design Notes

## Lecture 01 Cheat Sheet

### Core Concepts
* **HLD (High-Level Design):** Architecture decisions (what, where, how many).
* **LLD (Low-Level Design):** Code-level design (classes, interfaces, patterns).

### Scaling
* **Vertical Scaling:** Scale UP (bigger machine).
* **Horizontal Scaling:** Scale OUT (more machines).
    * Horizontal is the standard for production systems.
    * Introduces: sync, consistency, and load balancing issues.

### Protocols
* **HTTP:** Stateless, request-response, port 80.
* **HTTPS:** HTTP + TLS encryption, port 443.
* **WS (WebSocket):** Full-duplex, persistent, client ↔ server.
* **WebRTC:** P2P, real-time media, uses STUN/TURN.
* **SSE (Server-Sent Events):** Server → client one-way streaming.
* **gRPC:** Binary, HTTP/2, microservices.
* **SMTP:** Send email | **IMAP:** Read email.
* **FTP:** File transfer (legacy, use S3 instead).

### Transport Layer
* **TCP:** Reliable, ordered, 3-way handshake, slow.
* **UDP:** Unreliable, fast, no handshake, streaming.
* **QUIC:** UDP + reliability + encryption (HTTP/3).

### DNS (Domain Name System)
* **Purpose:** Domain → IP mapping.
* **Hierarchy:** Browser → OS → Resolver → Root → TLD → Authoritative NS.
* **Records:** A, AAAA, CNAME, NS, MX, TXT, SRV.
* **GeoDNS:** Route users to the nearest datacenter.

### Client-Server Model
1. **Client** → **DNS** → Get IP
2. **TCP + TLS** → **HTTP Request**
3. **Server processes**
4. **HTTP Response** → **Client renders**

### ⚠️ Key Interviewer Trap: WebSocket ≠ WebRTC
* **WebSocket:** Client ↔ Server (server is always involved).
* **WebRTC:** Client ↔ Client (peer-to-peer after initial signaling).
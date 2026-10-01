# System Design Notes


╔══════════════════════════════════════════════════════════╗
║              LECTURE 01 CHEAT SHEET                      ║
╠══════════════════════════════════════════════════════════╣
║                                                          ║
║  HLD = Architecture decisions (what, where, how many)    ║
║  LLD = Code-level design (classes, interfaces, patterns) ║
║                                                          ║
║  Vertical Scaling = Scale UP (bigger machine)            ║
║  Horizontal Scaling = Scale OUT (more machines)          ║
║  → Horizontal is standard for production systems         ║
║  → Introduces: sync, consistency, load balancing issues  ║
║                                                          ║
║  PROTOCOLS:                                              ║
║  HTTP    → Stateless, request-response, port 80          ║
║  HTTPS   → HTTP + TLS encryption, port 443               ║
║  WS      → Full-duplex, persistent, client↔server        ║
║  WebRTC  → P2P, real-time media, uses STUN/TURN          ║
║  SSE     → Server→client one-way streaming               ║
║  gRPC    → Binary, HTTP/2, microservices                 ║
║  SMTP    → Send email | IMAP → Read email                ║
║  FTP     → File transfer (legacy, use S3 instead)        ║
║                                                          ║
║  TCP     → Reliable, ordered, 3-way handshake, slow      ║
║  UDP     → Unreliable, fast, no handshake, streaming     ║
║  QUIC    → UDP + reliability + encryption (HTTP/3)       ║
║                                                          ║
║  DNS     → Domain → IP mapping                           ║
║  DNS Hierarchy: Browser → OS → Resolver → Root →         ║
║                 TLD → Authoritative NS                   ║
║  DNS Records: A, AAAA, CNAME, NS, MX, TXT, SRV           ║
║  GeoDNS  → Route users to nearest datacenter             ║
║                                                          ║
║  Client-Server Model:                                    ║
║  Client → DNS → Get IP → TCP+TLS → HTTP Request →        ║
║  Server processes → HTTP Response → Client renders       ║
║                                                          ║
║  KEY INTERVIEWER TRAP:                                   ║
║  WebSocket ≠ WebRTC                                      ║
║  WebSocket: Client ↔ Server (server always involved)     ║
║  WebRTC: Client ↔ Client (peer-to-peer after signaling)  ║
║                                                          ║
╚══════════════════════════════════════════════════════════╝
```
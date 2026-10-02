# 📘 Lecture 01: Introduction to HLD & Network Protocols

> **Part of:** System Design (HLD) Interview Preparation
> **Focus:** Foundations of High-Level Design, Client-Server Architecture, Scaling Strategies, and Network Protocols
> **Target:** Tier-1 MNC System Design Interviews

---

## 📑 Table of Contents

1. [Introduction to HLD vs LLD](#1-introduction-to-hld-vs-lld)
2. [Back-of-the-Envelope Estimation](#2-back-of-the-envelope-estimation)
3. [Client-Server Model](#3-client-server-model)
4. [Horizontal vs Vertical Scaling](#4-horizontal-vs-vertical-scaling)
5. [CAP Theorem (Primer)](#5-cap-theorem-primer)
6. [Network Communication & OSI Model](#6-network-communication--osi-model)
7. [Application Layer Protocols](#7-application-layer-protocols)
8. [Transport Layer Protocols](#8-transport-layer-protocols)
9. [DNS - Domain Name System](#9-dns---domain-name-system)
10. [REST, GraphQL & gRPC](#10-rest-graphql--grpc)
11. [Protocol Decision Matrix](#11-protocol-decision-matrix)
12. [Interview Questions & Follow-Ups](#12-interview-questions--follow-ups)
13. [Rapid Revision Cheat Sheet](#13-rapid-revision-cheat-sheet)

---

## 1. Introduction to HLD vs LLD

### 🎯 Definition

**High-Level Design (HLD)** focuses on the **architecture of an application** — the big-picture decisions about how components interact, scale, and communicate.

**Low-Level Design (LLD)** focuses on the **coding part** — class diagrams, design patterns, and detailed implementation of each component.

### 🏗️ HLD Decision Areas

| Area | What It Includes |
|------|-----------------|
| **Tech Stack** | MERN, Spring Boot, Django, etc. |
| **Cost Optimization** | Cloud provider, instance types, reserved vs on-demand |
| **Database Selection** | SQL, NoSQL, GraphQL, Graph DB, Time-series, Search |
| **Scaling Strategy** | 1,000 users → 10,000,000 users |
| **Back-of-the-Envelope Estimation** | QPS, storage, bandwidth calculations |
| **Non-Functional Requirements** | Availability, latency, consistency, fault tolerance |
| **Communication Patterns** | Sync (REST/gRPC), Async (Kafka/RabbitMQ) |

### 🔧 LLD Decision Areas

- **OOP Principles** (Encapsulation, Inheritance, Polymorphism, Abstraction)
- **Design Patterns** (Singleton, Factory, Observer, Strategy, etc.)
- **Clean Code** (SOLID principles)
- **Loose Coupling** (dependency injection, interfaces)

### 📊 HLD vs LLD Comparison

| Aspect | HLD | LLD |
|--------|-----|-----|
| **Analogy** | Blueprint of a mall | Wiring diagram of each shop |
| **Focus** | Components & interactions | Internal implementation |
| **Question** | "What components exist?" | "How is each coded?" |
| **Artifact** | Architecture diagram | Class diagrams, code |

---

## 2. Back-of-the-Envelope Estimation

### 🎯 Definition

Quick calculations to **estimate how many users your application can serve**, storage needed, bandwidth required, and number of servers.

### 📏 Key Numbers Every Engineer Must Know

```text
┌─────────────────────────────────────────────────────┐
│                  LATENCY NUMBERS                    │
├─────────────────────────────────────────────────────┤
│ L1 cache reference                → 0.5 ns          │
│ L2 cache reference                → 7 ns            │
│ Main memory (RAM) reference       → 100 ns          │
│ SSD random read                   → 150 μs          │
│ HDD disk seek                     → 10 ms           │
│ Send 1 MB over 1 Gbps network     → 10 ms           │
│ Read 1 MB sequentially from RAM   → 250 μs          │
│ Read 1 MB from SSD                → 1 ms            │
│ Read 1 MB from HDD                → 20 ms           │
│ Round trip within same datacenter → 500 μs          │
│ Round trip CA → Netherlands       → 150 ms          │
└─────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────┐
│               SCALE REFERENCE NUMBERS               │
├─────────────────────────────────────────────────────┤
│ 1 day                  = 86,400 sec ≈ 10^5          │
│ 1 month                ≈ 2.5 million sec            │
│ 1 char (ASCII)         = 1 byte                     │
│ 1 Image (compressed)   ≈ 300 KB                     │
│ 1 minute 720p video    ≈ 50 MB                      │
│ 1 Million              = 10^6                       │
│ 1 Billion              = 10^9                       │
│ Peak QPS               ≈ 2x to 5x of avg QPS        │
└─────────────────────────────────────────────────────┘
```

### 📝 Example: Estimate Twitter (X) Storage

**Assumptions:**
- 500 million tweets/day
- Average tweet size: 280 chars = 280 bytes

**Daily storage (text only):**
- 500M × 280B = 140 GB/day

**With metadata (user_id, timestamp, indexes):**
- ~3x = 420 GB/day

**With media (20% tweets, avg 300KB):**
- 100M × 300KB = 30 TB/day

**Long-term retention:**
- Per year: ~11 PB (media)
- 5-year retention: ~55 PB

---

## 3. Client-Server Model

### 🎯 Definition

A distributed application architecture where **clients request services** and **servers provide them** over a network.

### 🏗️ Architecture

```text
┌─────────┐       Request (HTTPS)       ┌─────────┐
│         │ ──────────────────────────────► │         │
│ CLIENT  │                             │ SERVER  │
│         │ ◄────────────────────────────── │         │
└─────────┘       Response (HTTPS)      └─────────┘
```

**Examples of Clients:**
- Web Browser
- Mobile App
- Desktop App
- CLI tool (curl)
- IoT device

**Examples of Servers:**
- Nginx / Apache
- Node.js / Spring Boot
- Django / Flask
- Go server
- Cloud Functions

### 🔄 Complete Workflow: "What Happens When You Type google.com?"

```text
Step 1: Browser checks LOCAL DNS CACHE
        │
Step 2: OS-level DNS cache check
        │
Step 3: Query DNS Resolver (ISP's DNS)
        │
Step 4: DNS Resolution Hierarchy
        ├─► Root DNS Server
        ├─► TLD Server (.com)
        └─► Authoritative Name Server
        │
Step 5: TCP 3-Way Handshake (port 443)
        │
Step 6: TLS Handshake (for HTTPS)
        │ ├── Client Hello
        │ ├── Server Hello + Certificate
        │ └── Session key established
        │
Step 7: HTTP Request sent over encrypted tunnel
        │
Step 8: Server processes, returns HTML/CSS/JS
        │
Step 9: Browser renders page (DOM, CSSOM, Render Tree)
```

---

## 4. Horizontal vs Vertical Scaling

### 🎯 Definition

- **Vertical Scaling (Scale UP):** Increase the resources (RAM, CPU, Disk) of a **single machine**.
- **Horizontal Scaling (Scale OUT):** Add **more machines** to distribute the load.

### 🏗️ Visualization

```text
    VERTICAL SCALING                     HORIZONTAL SCALING
      (Scale UP)                            (Scale OUT)

      ┌──────────┐                     ┌────┐  ┌────┐  ┌────┐
      │          │                     │ 32 │  │ 32 │  │ 32 │
      │  32→128  │                     │ GB │  │ GB │  │ GB │
      │    GB    │                     └────┘  └────┘  └────┘
      │          │                        
      └──────────┘                 + Load Balancer required
     Same machine,                     Multiple machines,
    more resources                      distribute load
```

### 📊 Detailed Comparison

| Dimension | Vertical Scaling | Horizontal Scaling |
|-----------|-----------------|-------------------|
| **What changes** | Bigger machine | More machines |
| **Complexity** | Simple (no code changes) | Complex (distributed systems) |
| **Cost curve** | Exponential | Linear |
| **Upper limit** | YES (hardware limits) | Practically NO |
| **Downtime** | YES (need restart) | NO (add nodes live) |
| **Single Point of Failure** | YES | NO |
| **Data consistency** | Easy | Hard (needs consensus) |
| **Load Balancer** | Not needed | Required |
| **Best for** | Small-medium apps | Large-scale apps |
| **Real-world example** | Upgrading EC2 instance | Adding more EC2 instances |

### ⚠️ Challenges of Horizontal Scaling

```text
Horizontal Scaling Challenges
│
├── 1. DATA SYNCHRONIZATION
│   └── Database replication (leader-follower)
│
├── 2. SESSION MANAGEMENT
│   ├── Sticky sessions (not recommended)
│   ├── Centralized session store (Redis) ✅
│   └── Stateless auth (JWT) ✅✅
│
├── 3. LOAD BALANCING
│   ├── Round Robin, Least Connections
│   ├── IP Hash, Consistent Hashing
│   └── Tools: Nginx, HAProxy, AWS ALB
│
├── 4. DATA PARTITIONING (Sharding)
│   ├── Range-based
│   ├── Hash-based
│   └── Directory-based
│
├── 5. DISTRIBUTED CONSENSUS
│   └── Paxos, Raft, Zab (ZooKeeper)
│
└── 6. NETWORK PARTITIONS
    └── CAP Theorem trade-offs
```

### 💡 Rule of Thumb

- **Vertical Scaling** → Better for **small user base** (simpler, faster to implement)
- **Horizontal Scaling** → Better for **large user base** (production-grade, resilient)

---

## 5. CAP Theorem (Primer)

### 🎯 Definition

In a distributed system, during a **network partition**, you can only guarantee **two out of three**:
- **C**onsistency (every read gets the latest write)
- **A**vailability (every request gets a response)
- **P**artition Tolerance (system works despite network failures)

```text
     Consistency ──────── Availability
          \                  /
           \                /
            \              /
             \  CAP       /
              \ THEOREM  /
               \        /
            Partition Tolerance
```

- **CP Systems:** MongoDB, HBase, Redis Cluster
- **AP Systems:** Cassandra, DynamoDB, CouchDB
- **CA Systems:** Traditional RDBMS (single node only)

> **In practice:** Partitions WILL happen, so you must choose between **C** or **A**.

---

## 6. Network Communication & OSI Model

### 🎯 Definition

**Network Communication** = Rules that both client and server follow to communicate.

**ISO-OSI Model** = 7-layer reference model that standardizes network communication.

### 🏗️ The 7 Layers

| Layer | Name | Protocols | HLD Relevance |
|-------|------|-----------|---------------|
| **7** | Application | HTTP, HTTPS, FTP, SMTP, WebSocket, DNS, gRPC | 🔴 HIGH |
| **6** | Presentation | SSL/TLS, Encryption, Compression | 🟡 MEDIUM |
| **5** | Session | NetBIOS, Session Management | 🟢 LOW |
| **4** | Transport | TCP, UDP, QUIC | 🔴 HIGH |
| **3** | Network | IP, ICMP, BGP | 🟡 MEDIUM |
| **2** | Data Link | Ethernet, MAC, ARP | 🟢 LOW |
| **1** | Physical | Cables, WiFi, Fiber | 🟢 LOW |

> **For HLD Interviews:** Focus on **Layer 7 (Application)** and **Layer 4 (Transport)**.

---

## 7. Application Layer Protocols

### 7.1 HTTP (HyperText Transfer Protocol)

#### 🎯 Definition
A **stateless**, request-response protocol used to transfer hypertext (HTML, API data) between client and server.

#### 🏗️ Architecture
```text
┌────────┐       HTTP Request       ┌────────┐
│ Client │ ──────────────────►      │ Server │
│        │ ◄──────────────────      │        │
└────────┘       HTTP Response      └────────┘
```

#### 📝 Request Structure

```http
GET /api/users/123 HTTP/1.1
Host: api.example.com
Authorization: Bearer <token>
Accept: application/json
Content-Type: application/json

{ "name": "John" }
```

#### 🔧 HTTP Methods
| Method | CRUD | Idempotent? |
|--------|------|-------------|
| GET | Read | ✅ Yes |
| POST | Create | ❌ No |
| PUT | Update | ✅ Yes |
| PATCH | Partial Update | ❌ No |
| DELETE | Delete | ✅ Yes |

#### 🚦 HTTP Status Codes
| Code | Meaning |
|------|---------|
| 1xx | Informational (100 Continue) |
| 2xx | Success (200 OK, 201 Created, 204 No Content) |
| 3xx | Redirection (301, 302, 304) |
| 4xx | Client Error (400, 401, 403, 404, 429) |
| 5xx | Server Error (500, 502, 503) |

#### 📈 HTTP Versions Evolution
| Version | Key Feature |
|---------|-------------|
| HTTP/1.0 | New TCP connection per request |
| HTTP/1.1 | Keep-alive, pipelining (but HOL blocking) |
| HTTP/2 | Multiplexing, server push, HPACK compression, binary |
| HTTP/3 | Built on QUIC (UDP), no TCP HOL blocking, faster setup |

#### ⚠️ Head-of-Line (HOL) Blocking
```text
HTTP/1.1:  ──[html]──[css]──[js]──  (sequential)

HTTP/2:    ──[html]──►              (multiplexed on
           ──[css ]──►               single conn, BUT
           ──[js  ]──►               TCP HOL still exists)

HTTP/3:    Each stream independent (no HOL blocking)
```
- **Default Port:** 80

### 7.2 HTTPS (HTTP Secure)

#### 🎯 Definition
HTTPS = HTTP + TLS (Transport Layer Security) encryption.

#### 🔐 TLS Handshake Workflow
```text
Client                              Server
  │                                   │
  │──── Client Hello ────────────────►│
  │     (TLS version, cipher suites)  │
  │                                   │
  │◄─── Server Hello ────────────────│
  │     (chosen cipher, certificate)  │
  │                                   │
  │  Verify cert with CA              │
  │                                   │
  │──── Key Exchange ────────────────►│
  │     (pre-master secret)           │
  │                                   │
  │     Both derive session key       │
  │                                   │
  │◄════ Encrypted Communication ════►│
  │     (symmetric encryption - AES)  │
```

#### 💡 Why Both Asymmetric & Symmetric Encryption?
Asymmetric (RSA) is ~1000x slower than symmetric (AES). Use asymmetric ONLY to exchange the symmetric key, then switch to symmetric for actual data transfer.
- **Default Port:** 443

### 7.3 FTP & SFTP

#### FTP (File Transfer Protocol)
Used when a client needs to send a file to the server (images, PDFs, etc.). Uses TWO connections:
- **Port 21:** Control channel
- **Port 20:** Data channel
- ⚠️ Sends credentials in plaintext — insecure.

#### SFTP (SSH File Transfer Protocol)
- Secured version of FTP — runs over SSH.
- Single connection on **Port 22**.
- Encrypted authentication + data transfer.
- **Modern HLD Alternative:** S3 pre-signed URLs, multipart upload, chunked transfer encoding.

### 7.4 SMTP, POP3, IMAP

#### SMTP (Simple Mail Transfer Protocol)
- To **SEND** email over the internet.
- **Default Port:** 25 (server-to-server), 587 (client-to-server)

#### POP3 (Post Office Protocol v3)
- To **RECEIVE**/download email to your device.
- Deletes email from the server by default.
- **Default Port:** 110

#### IMAP (Internet Message Access Protocol)
- To **READ** email while keeping it on the server.
- Syncs across multiple devices.
- **Default Port:** 143
- Used by Gmail, Outlook.

```text
SENDING:
Client ──SMTP──► Your Mail Server ──SMTP──► Recipient's Server

RECEIVING:
Recipient ──IMAP/POP3──► Mail Server
```

### 7.5 WebRTC

#### 🎯 Definition
Web Real-Time Communication — enables peer-to-peer audio, video, and data communication directly between browsers.

#### ⚡ Why WebRTC Exists?
HTTP/HTTPS limitations:
- Server cannot push to client (one-way initiation)
- Client-to-client communication via server has latency

WebRTC solves this by establishing a direct P2P connection after an initial signaling phase.

#### 🏗️ Architecture
```text
Client A                 Server              Client B
   │                       │                    │
   │── "I want to call B"─►│                    │
   │                       │── "A wants you" ──►│
   │                       │◄── SDP offer ─────│
   │◄── SDP Answer ───────│                    │
   │                       │                    │
   │   ICE Candidates exchanged (NAT traversal) │
   │                       │                    │
   │◄═══════ DIRECT P2P CONNECTION ════════════►│
   │         (UDP - for low latency)            │
```

#### 🔧 Key Components
| Component | Purpose |
|-----------|---------|
| **STUN Server** | Discovers public IP/port (NAT traversal) |
| **TURN Server** | Relay fallback when P2P fails (~15% cases) |
| **ICE** | Framework tries STUN first, falls back to TURN |
| **SDP** | Session Description Protocol (codecs, media info) |

- **Used by:** Google Meet, Discord, Zoom (partially), Facebook Messenger video.

### 7.6 WebSockets

#### 🎯 Definition
Full-duplex, bidirectional communication protocol between client and server over a single persistent TCP connection.

⚠️ **Important Clarification:** WebSocket is NOT direct client-to-client (that's WebRTC). The server IS involved — but both client and server can send messages at any time.

#### 🏗️ Architecture (Chat Example)
```text
Client A          Server              Client B
   │                 │                    │
   │═══ WS conn ════►│◄═══ WS conn ═════  │
   │                 │                    │
   │── "Hi B!" ─────►│                    │
   │                 │── "Hi B!" ────────►│
   │                 │                    │
   │                 │◄── "Hi A!" ────────│
   │◄── "Hi A!" ─────│                    │
```

#### 🔄 Connection Establishment
```http
# Client sends HTTP upgrade request
GET /chat HTTP/1.1
Upgrade: websocket
Connection: Upgrade
Sec-WebSocket-Key: dGhlIHNhbXBsZS...

# Server responds
HTTP/1.1 101 Switching Protocols
Upgrade: websocket
Connection: Upgrade
Protocol: ws:// or wss:// (secure)
Port: Same as HTTP (80) or HTTPS (443)
```

- **Use cases:** Chat apps, live sports scores, stock tickers, multiplayer games, collaborative editing.

### 7.7 Polling vs Long Polling vs SSE vs WebSocket

| Technique | Direction | Use Case |
|-----------|-----------|----------|
| **Short Polling** | Client → Server (repeated) | Simple dashboards, high latency acceptable |
| **Long Polling** | Client → Server (held open) | Early chat systems |
| **SSE** | Server → Client (one-way push) | News feeds, ChatGPT streaming, logs |
| **WebSocket** | Both ↔ (full duplex) | Real-time chat, gaming, collab tools |

```text
POLLING:              LONG POLLING:         SSE:                WEBSOCKET:
C ──"any?"──► S       C ──req──► S          C ──GET──► S        C ══upgrade══► S
C ◄──"no"──── S       │  (holds) │          C ◄──data1── S      C ◄══msg══════ S
(wait 5s)             │          │          C ◄──data2── S      C ══msg══════► S
C ──"any?"──► S       C ◄──data──S          (one-way)           (bidirectional)
```

---

## 8. Transport Layer Protocols

### 8.1 TCP (Transmission Control Protocol)

#### 🎯 Definition
Reliable, connection-oriented protocol that guarantees ordered delivery of data between client and server.

#### 🤝 3-Way Handshake (Connection Setup)
```text
Client                              Server
  │                                   │
  │──── SYN (seq=100) ──────────────►│  "Hey, want to talk?"
  │                                   │
  │◄─── SYN-ACK (seq=300,ack=101) ──│  "Yes, I hear you"
  │                                   │
  │──── ACK (ack=301) ──────────────►│  "Great, let's begin"
  │                                   │
  │═══════ CONNECTION ESTABLISHED ═══│
```
💡 **Why 3-way and not 2-way?** Both sides need to confirm they can send AND receive. Prevents zombie connections from delayed duplicate SYNs.

#### 📦 Data Transfer with ACKs
```text
Client                              Server
   │─── Packet P1 ───────────────────►│
   │◄── ACK ─────────────────────────│
   │─── Packet P2 ───────────────────►│
   │◄── ACK ─────────────────────────│
   │─── Packet P3 ───────────────────►│
   │◄── ACK ─────────────────────────│
```

#### ✅ TCP Guarantees
- Reliable delivery — retransmits lost packets
- Ordered delivery — reassembles in correct order
- Error detection — checksum on each segment
- Flow control — sliding window (receiver controls pace)
- Congestion control — slow start, AIMD algorithms
- **Used by:** HTTP, HTTPS, FTP, SMTP, databases

### 8.2 UDP (User Datagram Protocol)

#### 🎯 Definition
Unreliable, connectionless, fast protocol. Fire-and-forget packet delivery.

#### 🏗️ Workflow
```text
Client                              Server
  │                                   │
  │─── Packet P1 ───────────────────►│  (no ACK)
  │─── Packet P2 ───────────────────►│  (no ACK)
  │─── Packet P3 ───────────────────►│  (no ACK)
  │                                   │
  │ If packets are lost, dropped,     │
  │ or out-of-order → client          │
  │ doesn't care                      │
```

#### ❌ UDP Does NOT Provide
- No handshake
- No acknowledgments
- No ordering
- No congestion control

#### ✅ When to Use UDP
- Real-time audio/video (Google Meet, Zoom)
- Live streaming (Twitch, YouTube Live)
- Online gaming (position updates)
- DNS queries
- IoT sensor data

### 8.3 TCP vs UDP Comparison

| Feature | TCP | UDP |
|---------|-----|-----|
| **Connection** | Connection-oriented | Connectionless |
| **Handshake** | 3-way handshake | None |
| **Reliability** | Guaranteed delivery | Best effort |
| **Ordering** | In-order | No ordering |
| **Speed** | Slower | Faster |
| **Header size** | 20-60 bytes | 8 bytes |
| **Flow control** | Yes | No |
| **Congestion control** | Yes | No |
| **Broadcasting** | No | Yes |
| **Use cases** | Web, email, file transfer | Video calls, DNS, gaming |

### 8.4 QUIC Protocol

#### 🎯 Definition
QUIC (Quick UDP Internet Connections) — modern transport built on UDP that adds reliability + encryption. Powers HTTP/3.

#### ⚡ QUIC Advantages Over TCP
- 0-RTT connection setup (for returning clients)
- No head-of-line blocking (packet loss affects only one stream)
- Connection migration (seamless WiFi → 4G switch)
- Built-in TLS 1.3 encryption (always encrypted)
- **Used by:** Google, Cloudflare, Facebook, Akamai CDN, modern browsers.

---

## 9. DNS - Domain Name System

### 🎯 Definition
DNS = Domain Name System — the internet's phone book. Maps easy-to-remember domain names (google.com) to IP addresses (142.250.190.46).

#### 💡 Why DNS?
- Humans remember `google.com` easily.
- Computers need IP addresses like `142.250.190.46`.
- DNS bridges this gap.

### 🏗️ DNS Resolution Hierarchy
```text
User types: www.example.com
     │
     ▼
┌─────────────────────┐
│ 1. Browser DNS Cache│ ← Checked first
└──────────┬──────────┘
           │ miss
           ▼
┌─────────────────────┐
│ 2. OS DNS Cache     │ ← /etc/hosts
└──────────┬──────────┘
           │ miss
           ▼
┌─────────────────────┐
│ 3. ISP Resolver     │ ← or 8.8.8.8, 1.1.1.1
└──────────┬──────────┘
           │ miss
           ▼
┌─────────────────────┐
│ 4. Root DNS Servers │ ← 13 clusters worldwide
└──────────┬──────────┘
           │ "Ask .com TLD"
           ▼
┌─────────────────────┐
│ 5. TLD Server (.com)│
└──────────┬──────────┘
           │ "Ask example.com's NS"
           ▼
┌─────────────────────┐
│ 6. Authoritative NS │ ← Domain owner's DNS
└──────────┬──────────┘
           │ Returns IP: 93.184.216.34
           ▼
     IP cached at each level
```

### 📝 DNS Mapping Example
```text
youtube.com    ──► 120.52.5.6
instagram.com  ──► 130.53.4.8
```

### 📋 DNS Record Types
| Record | Purpose |
|--------|---------|
| **A** | Domain → IPv4 address |
| **AAAA** | Domain → IPv6 address |
| **CNAME** | Domain → Another domain (alias) |
| **NS** | Domain → Authoritative name servers |
| **MX** | Domain → Mail servers |
| **TXT** | Arbitrary text (SPF, DKIM, verification) |
| **SRV** | Service discovery (port + host) |
| **SOA** | Zone metadata |

### 🌍 DNS as a Load Balancing Tool
- **DNS Round Robin** — Returns different IPs in rotation.
- **GeoDNS** — Routes users to nearest datacenter (how CDNs work).
- **Weighted DNS** — 90% traffic to new version (canary).
- **Failover DNS** — Health check fails → return backup IP.
- **TTL (Time To Live):** How long DNS response is cached. Low TTL = fast failover but more queries. High TTL = fewer queries but slow failover.

---

## 10. REST, GraphQL & gRPC

### 📊 Comparison
| Feature | REST | GraphQL | gRPC |
|---------|------|---------|------|
| **Format** | JSON | JSON | Protobuf (binary) |
| **Protocol** | HTTP/1.1 | HTTP | HTTP/2 |
| **Contract** | OpenAPI/Swagger | Schema | .proto files |
| **Fetch** | Over/Under-fetch | Exact data | Exact data |
| **Speed** | Good | Good | Fastest |
| **Use Case**| Public APIs | Mobile apps | Microservices |
| **Used By** | Most public APIs | Facebook, GitHub | Google, Netflix, Uber |

### 🔧 gRPC Communication Patterns
- **Unary RPC** — 1 request, 1 response
- **Server Streaming** — 1 request, stream of responses
- **Client Streaming** — stream of requests, 1 response
- **Bidirectional Streaming** — both sides stream

---

## 11. Protocol Decision Matrix

| Scenario | Protocol Choice |
|----------|-----------------|
| Public API (CRUD) | REST over HTTPS |
| Internal microservices | gRPC |
| Real-time chat | WebSocket |
| Video/audio call | WebRTC + STUN/TURN |
| Live streaming (1→many) | HLS/DASH over HTTP |
| Server push (one-way) | SSE |
| Email sending | SMTP |
| Email reading | IMAP |
| File upload | HTTP multipart or S3 pre-signed URL |
| DNS resolution | DNS over UDP (port 53) |
| IoT sensor data | MQTT |
| Mobile (complex data) | GraphQL |
| Financial transactions | TCP |
| Gaming (position data) | UDP |
| Browser → CDN | HTTP/2 or HTTP/3 |

---

## 12. Interview Questions & Follow-Ups

**Q1: What happens when you type google.com in the browser?**
> Full flow: DNS cache → OS cache → Recursive resolver → Root → TLD → Authoritative → IP returned → TCP 3-way handshake → TLS handshake → HTTP request → Server processes → Response → Browser renders.

**Q2: When would you choose vertical scaling over horizontal?**
> Early stage startup, relational databases (initially), when consistency is critical. But always plan for horizontal scaling long-term.

**Q3: Why can't the server push data to the client using HTTP?**
> HTTP is request-response. Solutions: WebSocket (bidirectional), SSE (server push), Long Polling.

**Q4: Why does Google Meet use UDP, not TCP?**
> Real-time video prioritizes latency over reliability. A dropped frame is better than a delayed frame. TCP's retransmission causes buffering.

**Q5: How does WhatsApp deliver messages in real-time?**
> Persistent WebSocket connections. Server receives message from A, pushes to B via B's open WebSocket. If B is offline, message is queued.

**Q6: Difference between HTTP/2 and HTTP/3?**
> HTTP/2 uses TCP (still has TCP-level HOL blocking). HTTP/3 uses QUIC (UDP-based), eliminates HOL blocking, supports connection migration, 0-RTT resumption.

**Q7: If horizontal scaling needs data sync, why not always vertical?**
> Hardware limits, SPOF, no geographic distribution, exponential cost, downtime during upgrades.

**Q8: WebSocket vs WebRTC?**
> WebSocket: Client ↔ Server (full-duplex via server). WebRTC: Client ↔ Client (P2P after signaling).

---

## 13. Rapid Revision Cheat Sheet

```text
╔══════════════════════════════════════════════════════════╗
║              LECTURE 01 CHEAT SHEET                      ║
╠══════════════════════════════════════════════════════════╣
║                                                          ║
║  HLD = Architecture decisions                            ║
║  LLD = Code-level design                                 ║
║                                                          ║
║  Vertical Scaling   = Scale UP (bigger machine)          ║
║  Horizontal Scaling = Scale OUT (more machines)          ║
║                                                          ║
║  PROTOCOLS:                                              ║
║  HTTP     → Stateless, request-response, port 80         ║
║  HTTPS    → HTTP + TLS, port 443                         ║
║  WS       → Full-duplex, persistent, client↔server       ║
║  WebRTC   → P2P, real-time media, STUN/TURN              ║
║  SSE      → Server→client one-way streaming              ║
║  gRPC     → Binary, HTTP/2, microservices                ║
║  SMTP     → Send email | IMAP → Read email               ║
║  FTP/SFTP → File transfer                                ║
║                                                          ║
║  TCP   → Reliable, ordered, 3-way handshake              ║
║  UDP   → Unreliable, fast, no handshake                  ║
║  QUIC  → UDP + reliability + encryption (HTTP/3)         ║
║                                                          ║
║  DNS   → Domain → IP mapping                             ║
║  Hierarchy: Browser → OS → Resolver → Root →             ║
║             TLD → Authoritative NS                       ║
║                                                          ║
║  KEY TRAP:                                               ║
║  WebSocket ≠ WebRTC                                      ║
║  WebSocket: Client ↔ Server                              ║
║  WebRTC:    Client ↔ Client (P2P)                        ║
║                                                          ║
╚══════════════════════════════════════════════════════════╝
```

> **Next Lecture:** [Lecture 02 — Coming Soon]

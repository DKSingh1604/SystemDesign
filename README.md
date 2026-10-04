# HLD Notes from CoderArmy HLD Course
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

# 📘 Lecture 02: Scaling from 0 to Millions of Users

> **Part of:** System Design (HLD) Interview Preparation
> **Focus:** Evolving an application's architecture from a single server to a globally scaled, million-user system
> **Target:** Tier-1 MNC System Design Interviews

> **Golden Rule:** Everything we do in HLD should be to scale our application better.

---

## 📑 Table of Contents

1. [The Golden Framework](#1-the-golden-framework)
2. [Client-Server Architecture](#2-client-server-architecture)
3. [Choosing the Database (SQL vs NoSQL)](#3-choosing-the-database-sql-vs-nosql)
4. [Load Balancer](#4-load-balancer)
5. [Database Replication (Master-Slave)](#5-database-replication-master-slave)
6. [Cache](#6-cache)
7. [Content Delivery Network (CDN)](#7-content-delivery-network-cdn)
8. [Stateful vs Stateless Architecture](#8-stateful-vs-stateless-architecture)
9. [Multiple Datacenters (Geo-Routing)](#9-multiple-datacenters-geo-routing)
10. [Message Queues (Async Processing)](#10-message-queues-async-processing)
11. [Database Sharding](#11-database-sharding)
12. [API Gateway](#12-api-gateway)
13. [Complete Scaling Evolution](#13-complete-scaling-evolution)
14. [Interview Questions & Follow-Ups](#14-interview-questions--follow-ups)
15. [Rapid Revision Cheat Sheet](#15-rapid-revision-cheat-sheet)


---

## 1. The Golden Framework

### 🎯 Core Pattern

Every scaling decision in HLD follows ONE core pattern:

```text
┌──────────────────────────────────────────────────────────┐
│ 1. Identify the BOTTLENECK                               │
│ 2. Introduce a COMPONENT to solve it                     │
│ 3. The new component introduces NEW problems             │
│ 4. Repeat                                                │
└──────────────────────────────────────────────────────────┘
```

### 📈 The Scaling Journey

```text
Single Server → Separate DB → Multiple Servers → Load Balancer
→ DB Replication → Cache → CDN → Stateless + Shared Store
→ Multi-Datacenter → Message Queue → Sharding → Microservices
```

> **Interviewer's hidden rubric:** They want to see if you can **evolve** an architecture logically, not jump to "Kafka + Kubernetes + 50 microservices" on day 1.

---

## 2. Client-Server Architecture

### 🎯 Definition

The starting point of any application: a client requests, a server responds, and a database stores data.

### 🏗️ Workflow Diagram

```text
┌────────┐         1: URL        ┌─────┐
│ Client │ ─────────────────────►│ DNS │
│        │ ◄─────────────────────│     │
└───┬────┘         2: IP         └─────┘
    │
    │ 3: HTTP Request
    ▼
┌─────────────────┐
│   Web Server    │
│ (URL → IP map)  │
│                 │ ──4: Internal Mapping
└────────┬────────┘
    │ 5: DB query
    ▼
┌─────────┐
│   DB    │
└─────────┘
    │
    │ 6: HTML / JSON
    ▼
Back to Client
```

### 🏗️ Evolution Stages

#### Stage 1: Single Server (0 → ~1,000 users)

```text
┌────────┐          ┌─────────────────┐
│ Client │──HTTPS──►│    Monolith     │
│        │          │  ┌───────────┐  │
│        │◄──JSON───│  │ App Code  │  │
└────────┘          │  │ Database  │  │
                    │  │ Cache     │  │
                    │  └───────────┘  │
                    └─────────────────┘
```
✅ Simple to deploy
❌ Single Point of Failure
❌ Can't scale app and DB independently

#### Stage 2: Separate App & Database Server

```text
┌────────┐       ┌─────────┐       ┌─────────┐
│ Client │──────►│   App   │──────►│   DB    │
│        │       │ Server  │◄──────│ Server  │
└────────┘       └─────────┘       └─────────┘
```

**Why separate?**
- Scale INDEPENDENTLY (app needs more CPU, DB needs RAM)
- Choose different hardware optimizations
- DB can later be shared across multiple app servers
- Isolate failures

---

## 3. Choosing the Database (SQL vs NoSQL)

### 🎯 Definition

Databases are categorized into **Relational (SQL)** and **Non-Relational (NoSQL)**.

### 📊 Comparison

| Relational (SQL) | Non-Relational (NoSQL) |
|------------------|------------------------|
| MySQL | Key-Value Store — DynamoDB, Redis |
| PostgreSQL | Column-Family — Cassandra, HBase |
| Oracle SQL | Document Store — MongoDB, CouchDB |
| MS SQL Server | Graph DB — Neo4j, Amazon Neptune |

### 🧭 Decision Parameters

1. **Is data structured?** → Choose **Relational**
2. **Need low latency / massive scale?** → Choose **Non-Relational**

### ⚠️ Critical Clarification

> **GraphQL ≠ Graph DB**
>
> - **GraphQL** → A QUERY LANGUAGE for APIs (REST alternative). Developed by Facebook. Lets client request EXACTLY the fields it needs.
> - **Graph DB** → A DATABASE that stores data as nodes and edges. Examples: Neo4j, Amazon Neptune.

### 📊 SQL vs NoSQL Decision Matrix

| Criterion | Choose SQL | Choose NoSQL |
|-----------|-----------|--------------|
| **Data structure** | Structured, fixed schema | Unstructured, flexible |
| **ACID transactions** | Required | Not critical |
| **Relationships** | Many JOINs | Few / denormalized |
| **Scale pattern** | Vertical first | Horizontal |
| **Consistency need** | Strong | Eventual OK |
| **Query complexity** | Complex joins, aggregations | Simple key lookups |
| **Write-heavy?** | Moderate | Very high |
| **Schema evolution** | Rigid, migrations needed | Dynamic |

### 🗂️ The 4 Types of NoSQL

```text
KEY-VALUE STORE
"user:123" → "{...}"
Examples: Redis, DynamoDB, Memcached
Use: Caching, session store, shopping cart

DOCUMENT STORE
{ user: { name: "A", orders: [...] } }
Examples: MongoDB, CouchDB, Firestore
Use: Content mgmt, catalogs, user profiles

COLUMN-FAMILY (Wide-Column)
Row | Col1 Col2 Col3
Examples: Cassandra, HBase, ScyllaDB
Use: Time-series, analytics, write-heavy, IoT

GRAPH DB
(A)──friend──►(B)
Examples: Neo4j, Amazon Neptune
Use: Social networks, fraud detection, recommendations
```

### 🧪 ACID vs BASE

```text
ACID (Traditional SQL)           BASE (NoSQL)
═════════════════════            ════════════════════
Atomicity - All or nothing       Basically Available
Consistency - Valid state        Soft state
Isolation - Concurrent safe      Eventually consistent
Durability - Persists on crash   

ACID says: "We'd rather be slow and correct"
BASE says: "We'd rather be fast and eventually correct"
```

---

## 4. Load Balancer

### 🎯 Definition

A **Load Balancer (LB)** distributes incoming traffic across multiple servers to ensure no single server is overwhelmed.

### 🏗️ Architecture

```text
                               ┌──────────────┐
                 ┌────────┐    │ Load Balancer│    ┌──────────┐
                 │ Client │───►│ Public IP:   │───►│ Server 1 │
                 │        │    │ 123.23.4.4   │    │ 10.0.0.1 │
                 └────────┘    │              │    └──────────┘
                               │              │    ┌──────────┐
                               │              │───►│ Server 2 │
                               │              │    │ 10.0.0.2 │
                               └──────────────┘    └──────────┘
```

### 💡 Why Public IP for LB & Private IPs for Servers?

- **Security:** App servers are NOT exposed to the internet
- **Only LB is public** → reduces attack surface
- **Private IPs** allow internal communication only
- This is called a **DMZ (Demilitarized Zone)** pattern

### ⚙️ Load Balancing Algorithms

| Algorithm | How It Works | Pros / Cons |
|-----------|-------------|-------------|
| **Round Robin** | Rotate requests through servers | ✅ Simple ❌ Ignores load |
| **Weighted Round Robin** | S1 (wt 3), S2 (wt 1) | ✅ Handles heterogeneous servers |
| **Least Connections** | Routes to server with fewest active connections | ✅ Great for WebSockets |
| **Least Response Time** | Routes to lowest latency server | ✅ Performance-aware |
| **IP Hash** | `hash(client_IP) % N → server` | ✅ Session stickiness without cookies |
| **Consistent Hashing** ⭐ | Hash both servers & keys onto a ring | ✅ Minimal reshuffling on changes |

### 🧱 L4 vs L7 Load Balancer

| L4 Load Balancer (Transport Layer) | L7 Load Balancer (Application Layer) |
|-----------------------------------|-------------------------------------|
| Routes by IP + Port | Routes by URL, headers, cookies |
| Fast, low CPU | Slower, more CPU |
| No content inspection | Deep content inspection |
| Example: AWS NLB, HAProxy (TCP mode) | Example: AWS ALB, Nginx, HAProxy (HTTP mode) |
| Use: Gaming, raw TCP, databases | Use: Web apps, microservices, path routing |

### ⚠️ LB as a Single Point of Failure
**Solution:** ACTIVE-PASSIVE LB SETUP

```text
    ┌──────────────┐
    │  Active LB   │ ◄── All traffic
    │  (Primary)   │
    └──────┬───────┘
           │ heartbeat
    ┌──────┴───────┐
    │  Passive LB  │ ◄── Takes over if primary fails
    │  (Standby)   │
    └──────────────┘

Uses Virtual IP (VIP) — DNS points to VIP,
which floats between primary and standby.
```

---

## 5. Database Replication (Master-Slave)

### 🎯 Definition

**Replication** means copying data from one DB (Master) to one or more copies (Slaves). Reads are distributed across slaves, writes go only to master.

### 🏗️ Architecture

```text
               ┌─────────────┐
WRITES         │    MASTER   │
──────────────►│  (Primary)  │
               └──────┬──────┘
                      │ Replication
       ┌──────────────┼──────────────┐
       ▼              ▼              ▼
    ┌─────┐        ┌─────┐        ┌─────┐
    │Slave│        │Slave│        │Slave│
    │  1  │        │  2  │        │  3  │
    └──┬──┘        └──┬──┘        └──┬──┘
       └──────────────┴──────────────┘
                      ▲
                      │ READS
```

### 💡 Why This Helps

- Most apps are **READ-HEAVY** (80% reads, 20% writes)
- Distribute reads across N slaves → **N× read capacity**
- Backups taken from slaves (no master impact)
- Analytics queries on slaves (no master impact)

### 🔁 Replication Modes

#### Synchronous Replication
```text
Client ──write──► Master ──► Slave1 (OK)
                         └──► Slave2 (OK)
                         └──► Slave3 (OK)
Client ◄──ACK── Master (only after all slaves confirm)
```
- ✅ Zero data loss (strong consistency)
- ❌ SLOW — latency = slowest slave
- ❌ If a slave is down, writes STALL

#### Asynchronous Replication (Default)
```text
Client ──write──► Master ──ACK──► Client
                      │ (background)
                      └───► Slave1, Slave2, Slave3
```
- ✅ FAST writes
- ❌ Risk: Master crashes before replication → DATA LOSS
- ❌ REPLICATION LAG → stale reads from slaves

#### Semi-Synchronous (Sweet Spot)
Master waits for AT LEAST ONE slave to confirm.
Balances durability with latency.

### ⚠️ Replication Lag & Stale Reads
```text
Scenario: User posts a tweet, then immediately refreshes.

t=0ms: User POSTs tweet → Master DB
t=5ms: User GETs timeline → routed to Slave DB
t=5ms: Slave hasn't received the new tweet yet!
t=50ms: Replication completes

Result: User doesn't see their own tweet → re-posts → chaos.

Solutions:
1. READ-YOUR-WRITES CONSISTENCY — Route user's reads
   to MASTER for a short time after they write.
2. STICKY READS — Same user always reads from same replica.
3. MONOTONIC READS — User never sees older data than they
   already saw.
```

### 🚨 Master Failover
```text
Step 1: DETECT failure (heartbeat check)
Step 2: ELECT new master (Raft, Paxos, Orchestrator)
        → Choose slave with MOST RECENT data
Step 3: PROMOTE slave to master
Step 4: REROUTE writes (update DNS/service discovery)

⚠️ Risk: SPLIT-BRAIN
Old master wakes up → thinks it's still master.
Two masters accepting writes = data divergence disaster.

Solution: FENCING (STONITH - Shoot The Other Node In
The Head) → forcefully disable old master.
```

---

## 6. Cache

### 🎯 Definition

A **cache** is an in-memory storage layer between the app and the database that stores frequently accessed data for faster retrieval.

### 🏗️ Architecture
```text
┌─────────┐       ┌───────┐       ┌─────┐
│   App   │──►    │ Cache │──►    │ DB  │
│ Server  │       │(Redis)│       └─────┘
└─────────┘       └───────┘

Cache HIT → return from Cache (fast!)
Cache MISS → fetch from DB, store in Cache, return
```

### 💡 Why It Works

Reading from RAM is **~100,000× faster** than from disk:
- Disk (SSD): ~1 ms
- Memory (RAM): ~0.0001 ms (100 ns)

### 📋 Caching Strategies

#### 1. Cache-Aside (Lazy Loading) ⭐ Most Common
```text
App ──► Cache? ──miss──► DB ──► write to Cache
```
- ✅ Only cache what's used
- ❌ First request always slow
- ❌ Cache can go stale if DB is updated externally

#### 2. Read-Through
```text
App ──► Cache ──(on miss)──► DB
```
- ✅ Clean app code
- ❌ Requires cache library support

#### 3. Write-Through
```text
App ──write──► Cache ──► DB
```
- ✅ Cache always consistent with DB
- ❌ Higher write latency

#### 4. Write-Behind (Write-Back)
```text
App ──write──► Cache ──ACK──► App
                 │ (background batch)
                 └──► DB
```
- ✅ Super fast writes
- ❌ Data loss risk if cache crashes before flush

#### 5. Write-Around
```text
Writes: App ──► DB
Reads: App ──► Cache (miss) ──► DB
```
- ✅ Good for write-heavy with few re-reads
- ❌ Reads after writes are slow

### 🗑️ Cache Eviction Policies

| Policy | Description |
|--------|-------------|
| **LRU** | Least Recently Used — evict item unused longest (most common) |
| **LFU** | Least Frequently Used — evict item with fewest accesses |
| **FIFO** | First In First Out — simple queue |
| **TTL** | Time To Live — evict after fixed duration |
| **Random** | Random eviction — fast, surprisingly OK |
| **ARC** | Adaptive Replacement — combines LRU and LFU |

### ⚠️ Famous Caching Problems

#### Cache Stampede (Thundering Herd)
```text
Popular key expires → 10,000 requests miss cache
→ all hit DB → DB crashes.

Solutions:
• Mutex/Lock: Only 1 request fetches from DB
• Probabilistic early expiration: refresh before TTL
• Stale-while-revalidate: serve stale, refresh async
```

#### Cache Penetration
```text
Attacker queries non-existent keys repeatedly
→ every request misses → DB overloaded.

Solutions:
• Cache "null" results with short TTL
• Bloom filter to pre-check key existence
```

#### Cache Avalanche
```text
Many keys expire at the same time → mass cache miss
→ DB bombarded.

Solutions:
• Random jitter on TTLs (e.g., 300s ± 30s)
• Cache warming (pre-populate)
• Multi-layer cache (L1 app memory, L2 Redis)
```

### 🧩 Cache Technologies

| Technology | Characteristics |
|-----------|----------------|
| **Redis** ⭐ | Rich data structures, persistence, pub-sub, clustering |
| **Memcached** | Simple KV, pure in-memory, multi-threaded |
| **Hazelcast** | Distributed in-memory data grid (Java systems) |

---

## 7. Content Delivery Network (CDN)

### 🎯 Definition

A **CDN** is a **geographically distributed network of cache servers** that acts as a proxy, serving static content to users from the location closest to them.

> Examples: Amazon **CloudFront**, Netflix **OpenConnect**, Cloudflare, Akamai, Fastly.

### 🏗️ How CDN Works
```text
     ┌─── CDN Edge (Mumbai) ───┐
     │                         │
User(IN)─► Served from here    │
     │                         │
     └─────────────────────────┘

     ┌─── CDN Edge (Virginia) ─┐
     │                         │
User(US)─► Served from here    │
     │                         │
     └─────────────────────────┘
              │ cache miss
              ▼
     ┌──────────────────┐
     │  ORIGIN SERVER   │
     │   (Your App)     │
     └──────────────────┘
```

### 📋 What CDN Caches

- ✅ Static content: HTML, CSS, JS, images, videos, fonts
- ❌ Dynamic API responses (usually not cached)

### 📝 DNS Mapping with CDN
```text
After integrating CDN:
www.cloudfront.com/sing1 → 120.20.23.3

DNS returns IP of CLOSEST CDN edge.
Request goes to CDN first (not origin).
```

### 🔁 Push vs Pull CDN

#### Pull CDN (Most Common)
```text
• First user requests content → CDN fetches from origin
• CDN caches based on TTL
• Subsequent users served from cache

✅ No manual uploads needed
✅ Only caches what's actually requested
❌ First request is slow (cache miss)

Used by: Cloudflare, Fastly, CloudFront (default)
```

#### Push CDN
```text
• You proactively upload content to CDN
• Content ready before any user requests

✅ No cache miss penalty
✅ Good for very large, infrequent files
❌ Manual management overhead

Used for: Large video files, software downloads
```

### 🗑️ CDN Cache Invalidation

1. **Versioned URLs** (Best Practice): `styles.v123.css`
2. **Cache Busting with query params**: `styles.css?v=123`
3. **Cache Purge API**: Tell CDN to forget a URL
4. **Short TTL**: For frequently changed content

---

## 8. Stateful vs Stateless Architecture

### 🎯 Definition

- **Stateful:** Server stores client's session data locally
- **Stateless:** Server stores no session data; it's externalized to a shared store

> **Auto-scaling is not possible in a stateful architecture.**

### ❌ The Problem: Stateful (Sticky Sessions)
```text
User A ──login──► Server 1 [stores Session A]
User A ──later──► Server 2 [❌ "Who are you?"]

Workaround (BAD): Sticky Sessions
LB always routes User A → Server 1

❌ Problems:
• Can't autoscale
• Server crash = all its users logged out
• Uneven load (whales on one server)
• Can't do rolling deployments safely
```

### ✅ The Solution: Stateless Architecture
```text
User A ──► ANY Server ──► Session Store (Redis)
               ▲
User A ──► ANY Server ─────┘

✅ Benefits:
• Any server can handle any request
• Autoscaling works perfectly
• Server crash = user keeps session
• Rolling deploys with zero downtime
```

### 🔐 Session Management Strategies

| Strategy | Description |
|----------|-------------|
| **Centralized Session Store** | Session in Redis/Memcached, session ID in cookie |
| **JWT (JSON Web Tokens)** ⭐ | Session data encoded in token, no server storage |
| **Hybrid: JWT + Redis Blacklist** | JWT + Redis for token revocation |

#### JWT Structure
```text
header.payload.signature
{alg:HS256}.{userId:123,exp:...}.{HMAC}

✅ Fully stateless
✅ Great for microservices
❌ Hard to revoke (valid until expiry)
❌ Larger than session ID
```

### 🍪 Cookies vs Local Storage vs Session Storage

| Feature | Cookies | localStorage | sessionStorage |
|---------|---------|-------------|---------------|
| **Size limit** | 4 KB | 5-10 MB | 5-10 MB |
| **Sent to server** | YES (auto) | No | No |
| **Expiry** | Settable | Never | Tab close |
| **Accessible by JS** | Depends | Yes | Yes |
| **Use case** | Auth, prefs | User data | Temp data |

> **First-time request:** Cookies are saved on client. In every subsequent request, cookies are sent so server knows who the user is.

---

## 9. Multiple Datacenters (Geo-Routing)

### 🎯 Definition

Deploy servers in **multiple geographical regions** so users get low latency from the nearest datacenter.

### 🏗️ Architecture
```text
              GeoDNS / Anycast
                   │
     ┌─────────────┼─────────────┐
     ▼             ▼             ▼
 ┌────────┐    ┌────────┐    ┌────────┐
 │ DC-US  │    │ DC-EU  │    │ DC-ASIA│
 │        │    │        │    │        │
 │ LB     │    │ LB     │    │ LB     │
 │ Servers│    │ Servers│    │ Servers│
 │ Cache  │    │ Cache  │    │ Cache  │
 │ DB     │    │ DB     │    │ DB     │
 └────┬───┘    └────┬───┘    └────┬───┘
      └─────────────┼─────────────┘
                    │
            Global Shared DB
            (replication across DCs)
```

### 🌐 How GeoDNS Routes Users
```text
User in India types youtube.com:
→ DNS query goes to local resolver
→ Resolver detects user's IP → maps to India
→ DNS returns IP of DC-Asia
→ User connects to nearest DC

Methods:
1. GeoDNS (DNS-based) — Different IPs by region
2. Anycast IP — Same IP, routers find closest server
3. HTTP Redirect — App returns 302 to closest region
```

### 🔄 Data Consistency Across Datacenters

#### 1. Single Write Region, Global Read Replicas
```text
• All writes go to one region (e.g., US)
• Reads served locally in each region

✅ Simple ❌ Write latency for non-US users
```

#### 2. Multi-Master (Multi-Primary)
```text
• Every region can write
• Writes replicated to all other regions

✅ Fast writes everywhere
❌ CONFLICT RESOLUTION hell
```

#### 3. Regional Data Partitioning
```text
• User's data lives in their "home" region
• EU users' data in EU, US in US (GDPR compliant!)

✅ No conflicts
❌ Cross-region queries complex
```

### 🚨 Disaster Recovery Patterns

| Pattern | RTO | RPO | Description |
|---------|-----|-----|-------------|
| **Backup & Restore** | Hours | Hours | Daily backups to S3 |
| **Pilot Light** | 10s of min | Minutes | Minimal infra in DR region |
| **Warm Standby** | Minutes | Seconds | Scaled-down copy running |
| **Hot Standby / Active-Active** | Seconds | Near-zero | Full capacity in both regions |

> **RTO** = Recovery Time Objective (how fast to recover?)
> **RPO** = Recovery Point Objective (how much data loss acceptable?)

---

## 10. Message Queues (Async Processing)

### 🎯 Definition

A **Message Queue** decouples producers and consumers via an intermediate queue. Producer adds tasks → Consumer workers process them asynchronously.

> **This is also called the PUB-SUB (Publisher-Subscriber) model.**
> **Also called:** Fire-and-forget / asynchronous operation.
> **Examples:** Kafka, RabbitMQ, AWS SQS

### 🏗️ Architecture
```text
┌───────────┐       ┌───────────┐
│ Producer  │──push─►  QUEUE    │
│ (Web App) │       │ ████░░░░  │
└───────────┘       └─────┬─────┘
                          │ pull
            ┌─────────────┴─────────────┐
            ▼             ▼             ▼
        ┌───────┐     ┌───────┐     ┌───────┐
        │Worker1│     │Worker2│     │Worker3│
        └───────┘     └───────┘     └───────┘

Consumer takes a task from the queue, completes it,
then repeats. Producer keeps adding tasks independently.
```

### 💡 Benefits

- ✅ **Decoupling** — producer doesn't know about consumer
- ✅ **Load leveling** — handles traffic spikes
- ✅ **Scalability** — add workers independently
- ✅ **Reliability** — retry on failure
- ✅ Workers can be in different languages/services

### 📬 Queue vs Pub-Sub
```text
┌──────────────────────────────────────────────────────────┐
│                  QUEUE (Point-to-Point)                  │
├──────────────────────────────────────────────────────────┤
│ Publisher ──► [Queue] ──► Consumer A ✅                 │
│                     or Consumer B                       │
│                     or Consumer C                       │
│                                                          │
│ ONE message → ONE consumer                               │
│ Example: Task queue (video encoding jobs)                │
│ Tools: RabbitMQ, AWS SQS, Celery                         │
└──────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────┐
│                    PUB-SUB (Fan-out)                     │
├──────────────────────────────────────────────────────────┤
│ Publisher ──► [Topic] ──► Subscriber A ✅                 │
│                       ──► Subscriber B ✅                 │
│                       ──► Subscriber C ✅                 │
│                                                          │
│ ONE message → ALL subscribers                            │
│ Example: User signed up → notify Email, Analytics, CRM   │
│ Tools: Kafka (topics), AWS SNS, Google Pub/Sub           │
└──────────────────────────────────────────────────────────┘
```

### 📊 Kafka vs RabbitMQ vs SQS

| Feature | Kafka | RabbitMQ | AWS SQS |
|---------|-------|---------|---------|
| **Type** | Log/streaming | Traditional queue | Managed queue |
| **Model** | Pull-based | Push-based | Pull-based |
| **Throughput** | VERY HIGH (M/s) | HIGH (10K/s) | HIGH |
| **Persistence** | Days/weeks | Until consumed | Up to 14 days |
| **Message order** | Per partition | Per queue | FIFO option |
| **Replay msgs** | YES | NO | NO |
| **Use case** | Event streaming, analytics | Task queues, RPC | General async |
| **Famous users** | LinkedIn, Uber, Netflix | Instagram, Reddit | AWS customers |

### 🎯 Delivery Guarantees
```text
AT-MOST-ONCE
────────────
Message delivered 0 or 1 times. May be lost.
Use: Metrics, logs (loss OK)

AT-LEAST-ONCE (DEFAULT)
───────────────────────
Message delivered 1 or more times. Never lost.
Consumer must handle DUPLICATES (idempotency).
Use: Most real-world systems

EXACTLY-ONCE
────────────
Message delivered exactly 1 time.
Hardest to achieve. Often requires transactions.
Use: Financial transactions
```

### 🌍 Real-World Use Cases

- Image/video processing (Instagram, YouTube)
- Email/SMS sending (don't make user wait)
- Analytics events (Mixpanel, Amplitude)
- Order processing (Amazon)
- Log aggregation (ELK stack with Kafka)
- Microservice communication (event-driven architecture)

---

## 11. Database Sharding

### 🎯 Definition

**Sharding** (horizontal partitioning) splits data across multiple databases so each DB holds a subset of total data.

### 🏗️ Example
```text
Sharding key: id
Algorithm: id % 3 → DB

Original Table (TOO BIG):
┌─────┬──────────┐
│ id  │   name   │
│  1  │  Aditya  │
│  2  │  Err     │
│  3  │  Das     │
│  4  │  Sdas    │
└─────┴──────────┘

After Sharding (id % 3):
┌─ Shard 0 ─┐  ┌─ Shard 1 ─┐  ┌─ Shard 2 ─┐
│ id │ name │  │ id │ name │  │ id │ name │
│  3 │ Das  │  │  1 │ Adit │  │  2 │ Err  │
│  6 │ ...  │  │  4 │ Sdas │  │  5 │ ...  │
└───────────┘  └───────────┘  └───────────┘
```

### 🗂️ Sharding Strategies

#### 1. Range-Based
```text
id 1-1000 → Shard 1
id 1001-2000 → Shard 2
id 2001-3000 → Shard 3

✅ Simple, range queries efficient
❌ HOTSPOTS (new users all go to latest shard)
```

#### 2. Hash-Based
```text
shard = hash(id) % N

✅ Even distribution
❌ Can't do range queries
❌ RESHARDING is a NIGHTMARE
```

#### 3. Consistent Hashing ⭐
```text
Hash servers AND keys onto a circular ring.
Each key goes to next server clockwise.

  [S1]
 /    \
[k7] [k1]
/        \
[S4]     [S2]
\        /
[k5] [k3]
 \    /
  [S3]

Adding/removing a server only reshuffles K/N keys.
Used by: DynamoDB, Cassandra, CDNs, Memcached
```

#### 4. Geographic / Directory-Based
```text
Lookup service maps keys to shards.
EU users → EU shard, US users → US shard.

✅ Flexible, GDPR compliant
❌ Lookup service = extra hop + SPOF
```

### 🎯 Choosing a Sharding Key

A good sharding key has:
- ✅ **High cardinality** (many unique values)
- ✅ **Even distribution** (no hotspots)
- ✅ **Query locality** (most queries filter by this key)

BAD examples:
- ❌ Gender (only 2-3 values)
- ❌ Country (US/China dominate → hotspots)
- ❌ Timestamp (new writes all go to latest shard)

GOOD examples:
- ✅ user_id (random, high cardinality)
- ✅ Composite keys like (user_id, timestamp)

> **ANTI-PATTERN: "Celebrity problem"**
> If one user has 100M followers, their shard gets overwhelmed.
> Solution: Special-case celebrity accounts into their own shards.

### ⚠️ Downsides of Sharding
```text
CROSS-SHARD QUERIES ARE PAINFUL
SELECT COUNT(*) FROM users WHERE country='IN'
→ Must query ALL shards and aggregate ("scatter-gather")

JOINS BECOME HARD/IMPOSSIBLE
If users and orders are on different shards.

TRANSACTIONS ACROSS SHARDS
Need distributed transactions (2PC) → slow, complex.

RESHARDING IS BRUTAL
Billions of rows to migrate while system is live.

OPERATIONAL OVERHEAD
More DBs = more monitoring, backups, failovers.

Rule: Shard ONLY when you have no choice.
Try read replicas, caching, denormalization first.
```

### 🔄 Data Denormalization
```text
Normalized (SQL best practice):
users table: id, name, email
orders table: id, user_id, product

To get user name + orders:
SELECT u.name, o.product
FROM users u JOIN orders o ON u.id = o.user_id
JOIN is EXPENSIVE at scale.

Denormalized (NoSQL style):
orders table: id, user_id, user_name, user_email, product

Query: SELECT * FROM orders (no JOIN!)

✅ Fast reads
❌ Data duplication
❌ Updates are painful

When to denormalize:
• Read-heavy workloads
• Reads must be sub-millisecond
• Data rarely changes
```

---

## 12. API Gateway

### 🎯 Definition

An **API Gateway** is a single entry point for all client requests to a microservices backend.

### 🏗️ Architecture
```text
     ┌──────────────┐
Client ──► API Gateway  │
     └──────┬───────┘
            │
  ┌─────────┼─────────┐
  ▼         ▼         ▼
┌──────┐  ┌──────┐  ┌───────┐
│ Auth │  │ User │  │ Order │
│ Svc  │  │ Svc  │  │ Svc   │
└──────┘  └──────┘  └───────┘
```

### 📋 Responsibilities

- Authentication / Authorization
- Rate limiting / Throttling
- Request routing
- Response aggregation
- Caching
- Logging / Monitoring
- SSL termination
- Request/response transformation
- API versioning

### 🧰 Tools

Kong, AWS API Gateway, Apigee, Nginx, Zuul (Netflix), Envoy

---

## 13. Complete Scaling Evolution

This is EXACTLY how to walk through a system design question:
```text
STAGE 1: 1 user
└── Single server (app + DB together)

STAGE 2: 100 users
└── Separate DB from app server

STAGE 3: 1,000 users
└── Add Load Balancer + Multiple app servers
└── Introduce Master-Slave DB Replication

STAGE 4: 10,000 users
└── Add Cache (Redis)
└── Add CDN for static content

STAGE 5: 100,000 users
└── Move to Stateless architecture
└── Session store in Redis / Use JWT
└── Auto-scaling enabled

STAGE 6: 1,000,000 users
└── Multiple Datacenters (Geo-routing)
└── Message Queues for async work
└── Database Sharding

STAGE 7: 10,000,000+ users
└── Microservices + API Gateway
└── Service Mesh (Istio, Linkerd)
└── Event-driven architecture (Kafka)
└── Multi-region multi-master DBs
└── Custom caching layers
└── Advanced observability
```

---

## 14. Interview Questions & Follow-Ups

### Q1: If your master DB goes down, how do you ensure no data loss?
> Semi-synchronous replication + persistent WAL (Write-Ahead Logs) + fencing for split-brain prevention.

### Q2: You added cache, but users still see stale data. Why?
> Cache invalidation issues. Discuss write-through, TTL tuning, and cache-aside pitfalls.

### Q3: Your LB is now the bottleneck. What next?
> DNS load balancing (multiple LB IPs), Anycast IP, or active-active LB cluster.

### Q4: A specific shard is overloaded (hotspot). Fix it.
> Re-shard with a better key, use consistent hashing, special-case the hot entity.

### Q5: How would you migrate from a monolith DB to sharded DBs with zero downtime?
> Dual writes → backfill historical data → shadow reads for validation → cutover reads → remove old writes.

### Q6: Why not just put everything in Redis and skip the DB?
> Durability (data loss on crash), cost (RAM >> disk), query capability (no complex joins).

### Q7: Design the system to handle 10x traffic spike during Super Bowl ad.
> Pre-scale, CDN, aggressive caching, message queues for async work, circuit breakers, graceful degradation.

### Q8: What if your message queue goes down?
> Clustered queue (Kafka with multiple brokers), persistent storage, dead-letter queues, idempotent consumers.

---

## 15. Rapid Revision Cheat Sheet
```text
╔══════════════════════════════════════════════════════════╗
║             LECTURE 02 — SCALING CHEAT SHEET             ║
╠══════════════════════════════════════════════════════════╣
║                                                          ║
║ COMPONENT      SOLVES                                    ║
║ ─────────      ──────                                    ║
║ Separate DB  → Independent scaling of app vs DB          ║
║ Load Balancer→ Distribute traffic, hide servers          ║
║ Replication  → Read scaling, fault tolerance             ║
║ Cache        → Latency, DB load reduction                ║
║ CDN          → Static content delivery, geo-latency      ║
║ Stateless    → Horizontal scaling, auto-scaling          ║
║ Multi-DC     → Global latency, disaster recovery         ║
║ Message Queue→ Async work, decoupling, spike handle      ║
║ Sharding     → Write scaling, data volume                ║
║ API Gateway  → Microservices entry, cross-cutting        ║
║                                                          ║
║ KEY DECISIONS:                                           ║
║ • SQL vs NoSQL       → structured + ACID vs scale + flex ║
║ • Sync vs Async rep  → consistency vs latency            ║
║ • Cache-aside vs W-T → simplicity vs consistency         ║
║ • L4 vs L7 LB        → speed vs intelligence             ║
║ • Queue vs Pub-Sub   → 1-to-1 vs 1-to-many               ║
║ • Hash vs Range      → distribution vs range query       ║
║                                                          ║
║ TRAPS TO AVOID:                                          ║
║ • GraphQL ≠ Graph DB                                     ║
║ • Sticky sessions (anti-pattern)                         ║
║ • Sharding too early                                     ║
║ • Ignoring cache invalidation                            ║
║ • Treating LB as infallible (it's an SPOF too!)          ║
║                                                          ║
╚══════════════════════════════════════════════════════════╝
```

---

⭐ If you found this helpful, please star the repository!

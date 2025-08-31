# Omni Server - Client/Server Model

## Overview

Omni Server is a modern C++ HTTPS server implementation built on a client-server architecture model. This project features a multithreaded SSL server with API endpoints, custom logging capabilities, and JSON handling using the nlohmann/json library.

## Key Features

- **SSL/TLS Encryption**: Secure communications using OpenSSL with self-signed certificates
- **Multithreading Support**: Configurable thread pool for handling concurrent requests
- **Custom Logging**: Integrated with a proprietary logging library supporting JSON format
- **RESTful API**: Multiple endpoints with JSON responses (under development)
- **Health Monitoring**: Built-in health check endpoint for system monitoring
- **Automatic Certificate Generation**: Self-signed SSL certificate generation at runtime

## Deployment Scripts

The project includes shell scripts for easy AWS deployment:

### `deploy-aws.sh`
```bash
#!/bin/bash
``````
 Automated deployment script for AWS EC2
- Handles instance setup, dependencies, and service configuration
- Technology Stack
- **C++17**: Modern C++ standards compliance
- **httplib**: HTTP server library for endpoint handling
- **nlohmann/json**: JSON parsing and serialization
- **OpenSSL**: SSL/TLS encryption support
- **Custom Logging Library**: Proprietary logging system with JSON formatting
- **Multi-threading**: std::thread for concurrent request processing

## SSL Certificate Setup

The server automatically generates self-signed SSL certificates at runtime:
- Certificates are stored in `runtime_deps/` directory
- Auto-generated if missing using OpenSSL commands
- Valid for 365 days with localhost CN

## API Endpoints (Under Development)

### Current Endpoints:
- `GET /` - Server information and available endpoints
- `GET /health` - Health status check returns JSON with system status

### Planned Endpoints:
- Additional API endpoints are currently under development
- More functionality will be added in future releases

## Building and Running

1. Ensure OpenSSL development libraries are installed
2. Compile with C++17 support
3. Run the server executable
4. Server starts on `0.0.0.0:9000` by default

## Logging

The server uses a custom logging library with:
- JSON-formatted log output
- Log rotation (5 files maximum)
- Log storage in `../logs` directory
- Real-time logging to console

## Usage

```bash
# Start the server
./omni_server

# Test health endpoint
curl -k https://localhost:9000/health

# Test root endpoint
curl -k https://localhost:9000/



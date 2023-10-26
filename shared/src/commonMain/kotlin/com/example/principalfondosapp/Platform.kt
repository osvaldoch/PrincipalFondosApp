package com.example.principalfondosapp

interface Platform {
    val name: String
}

expect fun getPlatform(): Platform
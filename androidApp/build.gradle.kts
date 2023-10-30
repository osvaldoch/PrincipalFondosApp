plugins {
    id("com.android.application")
    kotlin("android")

    id("kotlin-kapt")

}

android {
    namespace = "com.example.principalfondosapp.android"
    compileSdk = 34
    defaultConfig {
        applicationId = "com.example.principalfondosapp.android"
        minSdk = 26
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"
    }
    buildFeatures {
        compose = true
    }
    composeOptions {
        //kotlinCompilerExtensionVersion = libs.versions.compose.compiler.get()
        kotlinCompilerExtensionVersion = "1.4.0"

    }
    packagingOptions {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }
    buildTypes {
        getByName("release") {
            isMinifyEnabled = false
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
    kotlinOptions {
        //jvmTarget = "1.8"
        jvmTarget = "17"

    }
}

dependencies {
    implementation(project(":shared"))
    implementation("androidx.compose.ui:ui:1.4.3")
    implementation("androidx.compose.ui:ui-tooling:1.4.3")
    implementation("androidx.compose.ui:ui-tooling-preview:1.4.3")
    implementation("androidx.compose.foundation:foundation:1.4.3")
    implementation("androidx.compose.material:material:1.4.3")
    implementation("androidx.activity:activity-compose:1.7.1")
    implementation(libs.compose.material3)

    implementation("org.jetbrains.kotlinx:atomicfu:0.20.2")


    implementation(libs.dagger)
    kapt(libs.google.dagger.compiler)

    implementation(
        fileTree(
            mapOf(
                "dir" to "libs",
                "include" to listOf("*.aar", "*.jar")
            )
        )
    )


    //Retrofit
    implementation("com.squareup.retrofit2:retrofit:2.9.0")
    implementation("com.squareup.retrofit2:converter-gson:2.9.0")
    implementation("com.squareup.retrofit2:adapter-rxjava2:2.9.0")
    implementation("com.squareup.okhttp3:logging-interceptor:4.9.0")

    implementation("io.reactivex.rxjava2:rxandroid:2.1.1")

    // Rx


}

buildscript {
    dependencies {
        // Use the same version in the error
        classpath("org.jetbrains.kotlinx:atomicfu-gradle-plugin:0.17.3")
    }
}

allprojects {
    apply(plugin = "kotlinx-atomicfu")
}
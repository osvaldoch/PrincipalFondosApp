plugins {
    //trick: for the same plugin versions in all sub-modules
/*
    alias(libs.plugins.androidApplication).apply(false)
    alias(libs.plugins.androidLibrary).apply(false)
    alias(libs.plugins.kotlinAndroid).apply(false)
    alias(libs.plugins.kotlinMultiplatform).apply(false)
    alias(libs.plugins.kotlinCocoapods).apply(false)

    id("org.jetbrains.compose").version("1.5.1") apply false

*/


    //trick: for the same plugin versions in all sub-modules
    kotlin("multiplatform").version("1.8.0").apply(false)
    id("org.jetbrains.compose").version("1.4.0") apply false

    id("com.android.application") version "8.1.0" apply false
    id("com.android.library") version "8.1.0" apply false
    id("org.jetbrains.kotlin.android") version "1.5.31" apply false
}

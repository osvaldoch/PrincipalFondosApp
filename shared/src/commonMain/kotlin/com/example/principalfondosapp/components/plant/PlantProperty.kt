package com.example.principalfondosapp.components.plant

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import com.example.principalfondosapp.components.CircularProgress
import com.example.principalfondosapp.model.Plant



@Composable
internal fun PlantProperty(currentItem: Plant, modifier: Modifier) {
    Column(
        modifier = modifier,
        verticalArrangement = Arrangement.spacedBy(19.dp)
    ) {
        repeat(currentItem.properties.size) {
            CircularProgress(currentItem.properties[it])
        }
    }
}


package com.example.principalfondosapp.model


data class Plant(
    val name: String? = "",
    val properties: List<Properties> =
        listOf(
            Properties("Peso"),
            Properties("Altura"),
            Properties("Agua"),
        ),
    val image: String? = null
) {

    companion object{
        fun getPlantList(): List<Plant> {

            return listOf(
                Plant("Agave", image = "Plants1.jpg"),
                Plant("Nolina", image = "Plants2.jpg"),
                Plant("Palmera", image = "Plants3.jpg"),
                Plant("Cactus", image = "Plants1.jpg"),
                Plant("Maguey", image = "Plants2.jpg"),
                Plant("Nopal", image = "Plants3.jpg"),
            )
        }
    }

}

data class Properties(
    val propertyName: String,
    val percent: Float = (0 until 100).random().toFloat()/100
)

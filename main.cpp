//
// Created by Flavia Rivero on 13/12/24.
//

#include "main.h"
#include "include/variant.h"
#include <iostream>

int main() {
    // Crear instancias de Variant con diferentes tipos y valores
    Variant v1(Symbol, "x");
    Variant v2(Number, "42");
    Variant v3(Cadena, "Hola, mundo, soy Flavia!");

    // Imprimir las variantes como cadenas
    std::cout << v1.to_string() << std::endl;
    std::cout << v2.to_string() << std::endl;
    std::cout << v3.to_string() << std::endl;

    // Convertir las variantes a cadenas JSON y imprimirlas
    std::cout << v1.to_json_string() << std::endl;  // Debería imprimir un JSON con el símbolo
    std::cout << v2.to_json_string() << std::endl;  // Debería imprimir un JSON con el número
    std::cout << v3.to_json_string() << std::endl;  // Debería imprimir un JSON con la cadena

    // Crear una Variant desde una cadena JSON
    std::string json_str = "{\"value\":\"y\", \"type\":\"Symbol\"}";
    Variant v4 = Variant::from_json_string(json_str);  // Debería crear un símbolo con el valor "y"

    // Imprimir la variante creada desde JSON
    std::cout << v4.to_string() << std::endl;

    return 0;
}

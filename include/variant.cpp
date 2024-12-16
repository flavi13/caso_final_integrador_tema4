//
// Created by Flavia Rivero on 15/12/24.
//

#include "variant.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include "json11.hpp"  // Incluimos la biblioteca json11 para manejar JSON

// Constructores
Variant::Variant(variant_type type) : type(type), env(nullptr), proc(nullptr) {}

// Constructor que inicializa el tipo y valor de la variante
Variant::Variant(variant_type type, const std::string& val) : type(type), val(val), env(nullptr), proc(nullptr) {}

// Constructor que inicializa la variante como un procedimiento
Variant::Variant(proc_type proc) : type(Proc), proc(proc), env(nullptr) {}

// Métodos
std::string Variant::to_string() {
    // Convertir el valor de la variante a una cadena según su tipo
    switch (type) {
        case Symbol:
            return val;  // Para símbolos, devolver el valor tal cual
        case Number:
            return val;  // Para números, devolver el valor
        case Cadena:
            return "\"" + val + "\"";  // Para cadenas, ponerlo en comillas dobles
        case List: {
            std::string r = "(";
            for (size_t i = 0; i < list.size(); i++) {
                r += list[i].to_string();
                if (i < list.size() - 1) r += " ";  // Añadir un espacio entre los elementos
            }
            r += ")";
            return r;
        }
        case Proc:
            return "<proc>";
        case Lambda:
            return "<lambda>";
    }
    return "<unknown>";  // Si el tipo no es reconocido, devolver "<unknown>"
}

std::string Variant::to_json_string() {
    using namespace json11;

    Json::object obj;
    obj["type"] = variant_type_to_string(type);  // Convertir el tipo de variante a cadena y añadirlo al objeto JSON

    switch (type) {
        case Symbol:
        case Number:
        case Cadena:
            obj["value"] = val;  // Para estos tipos, añadir el valor al objeto JSON
            break;
        case List: {
            std::vector<Json> jlist;
            for (auto &elem : list) {
                std::string elem_json = elem.to_json_string();  // Convertir cada elemento de la lista a JSON string
                std::string err;
                Json subjob = Json::parse(elem_json, err);  // Parsear el JSON string a un objeto JSON
                if (!err.empty()) {
                    throw std::runtime_error("Error al parsear elemento de la lista a JSON: " + err);
                }
                jlist.push_back(subjob);  // Añadir el objeto JSON al vector
            }
            obj["list"] = jlist;  // Añadir la lista al objeto JSON
            break;
        }
        case Proc:
        case Lambda:
            break;
    }

    Json j(obj);
    return j.dump();  // Convertir el objeto JSON a cadena y devolverlo
}

// Métodos estáticos
Variant Variant::from_json_string(std::string sjson) {
    std::string err;
    json11::Json job = json11::Json::parse(sjson, err);
    if (!err.empty()) {
        throw std::runtime_error("Error al parsear JSON: " + err);
    }
    return parse_json(job);  // Llamar a parse_json() para convertir el objeto JSON a una variante
}

Variant Variant::parse_json(const json11::Json &job) {
    std::string t = job["type"].string_value();
    if (t.empty()) {
        throw std::runtime_error("El JSON no contiene el campo 'type' o no es una cadena");
    }

    variant_type vtype = string_to_variant_type(t);   // Convertir la cadena del tipo a variant_type

    Variant var(vtype);
    switch (vtype) {
        case Symbol:
        case Number:
        case Cadena:
            var.val = job["value"].string_value();  // Obtener el valor desde el JSON
            break;
        case List: {
            auto arr = job["list"].array_items();  // Obtener la lista desde el JSON
            for (auto &elem : arr) {
                Variant v = Variant::parse_json(elem);
                var.list.push_back(v);  // Añadir el elemento parseado a la lista
            }
            break;
        }
        case Proc:
        case Lambda:
            break;
    }

    return var;
}

// Funciones auxiliares
static std::string variant_type_to_string(variant_type t) {
    // Convertir variant_type a string
    switch (t) {
        case Symbol: return "Symbol";
        case Number: return "Number";
        case List: return "List";
        case Proc: return "Proc";
        case Lambda: return "Lambda";
        case Cadena: return "Cadena";
    }
    return "Unknown";
}

static variant_type string_to_variant_type(const std::string &s) {
    // Convertir string a variant_type
    if (s == "Symbol") return Symbol;
    if (s == "Number") return Number;
    if (s == "List") return List;
    if (s == "Proc") return Proc;
    if (s == "Lambda") return Lambda;
    if (s == "Cadena") return Cadena;
    throw std::runtime_error("Tipo desconocido: " + s);
}
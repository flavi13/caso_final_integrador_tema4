//
// Created by Flavia Rivero on 15/12/24.
//

#include <vector>
#include <string>
#include <map>
#include "json11.hpp"

#ifndef VARIANT_H
#define VARIANT_H


// Enumeración para los diferentes tipos de Variant
enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

// Definición de Entorno
struct Entorno {
};

// Clase Variant
class Variant {
public:
    typedef Variant(*proc_type)(const std::vector<Variant>&);
    typedef std::vector<Variant>::const_iterator iter;
    typedef std::map<std::string, Variant> map;

    variant_type type;
    std::string val;
    std::vector<Variant> list;
    proc_type proc;
    Entorno* env;

    // Constructores
    Variant(variant_type type = Symbol);
    Variant(variant_type type, const std::string& val);
    Variant(proc_type proc);

    // Métodos
    std::string to_string();
    std::string to_json_string();

    // Métodos estáticos
    static Variant from_json_string(std::string json_str);
    static Variant parse_json(const json11::Json &job);
};

// Funciones auxiliares
static std::string variant_type_to_string(variant_type t);
static variant_type string_to_variant_type(const std::string &s);

#endif // VARIANT_H
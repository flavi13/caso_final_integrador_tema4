#include "../include/variant.h"
#include<string>
#include <vcpkg/installed/x64-windows/share/json11/json11.hpp>


Variant::Variant(variant_type type) : type(type), env(nullptr), proc(nullptr) {}
Variant::Variant(variant_type type, const std::string& val) : type(type), val(val), env(nullptr), proc(nullptr) {}
Variant::Variant(proc_type proc) : type(Proc), proc(proc), env(nullptr) {}

std::string Variant::to_string() {
    switch(type) {
        case Symbol: return "Symbol(" + val + ")";
        case Number: return "Number(" + val + ")";
        case List: {
            std::string result = "List(";
            for (const auto& item : list) {
                result += item.to_string() + ", ";
            }
            result += ")";
            return result;
        }
        case Proc: return "Proc";
        case Lambda: return "Lambda";
        case Cadena: return "Cadena(" + val + ")";
        default: return "Unknown";
    }
}

std::string Variant::to_json_string() {
    json11::Json json_obj;
    switch(type) {
        case Symbol: json_obj = json11::Json::object{{"Symbol", val}}; break;
        case Number: json_obj = json11::Json::object{{"Number", val}}; break;
        case List: {
            std::vector<json11::Json> json_list;
            for (const auto& item : list) {
                json_list.push_back(item.to_json_string());
            }
            json_obj = json11::Json::array(json_list);
            break;
        }
        case Proc: json_obj = json11::Json::object{{"Proc", "function"}}; break;
        case Lambda: json_obj = json11::Json::object{{"Lambda", "function"}}; break;
        case Cadena: json_obj = json11::Json::object{{"Cadena", val}}; break;
        default: json_obj = json11::Json::object{{"Unknown", ""}}; break;
    }
    return json_obj.dump();
}

Variant Variant::from_json_string(const std::string& sjson) {
    std::string err;
    auto json_obj = json11::Json::parse(sjson, err);
    if (!err.empty()) throw std::runtime_error("Error parsing JSON: " + err);

    Variant var;
    if (json_obj.is_object()) {
        const auto& obj = json_obj.object_items();
        if (obj.find("Symbol") != obj.end()) {
            var.type = Symbol;
            var.val = obj.at("Symbol").string_value();
        } else if (obj.find("Number") != obj.end()) {
            var.type = Number;
            var.val = obj.at("Number").string_value();
        } else if (obj.find("List") != obj.end()) {
            var.type = List;
            for (const auto& item : obj.at("List").array_items()) {
                var.list.push_back(from_json_string(item.dump()));
            }
        } else if (obj.find("Cadena") != obj.end()) {
            var.type = Cadena;
            var.val = obj.at("Cadena").string_value();
        }
    }
    return var;
}

Variant Variant::parse_json(const json11::Json& job) {
    Variant var;
    if (job.is_object()) {
        const auto& obj = job.object_items();
        if (obj.find("Symbol") != obj.end()) {
            var.type = Symbol;
            var.val = obj.at("Symbol").string_value();
        } else if (obj.find("Number") != obj.end()) {
            var.type = Number;
            var.val = obj.at("Number").string_value();
        } else if (obj.find("List") != obj.end()) {
            var.type = List;
            for (const auto& item : obj.at("List").array_items()) {
                var.list.push_back(parse_json(item));
            }
        } else if (obj.find("Cadena") != obj.end()) {
            var.type = Cadena;
            var.val = obj.at("Cadena").string_value();
        }
    }
    return var;
}

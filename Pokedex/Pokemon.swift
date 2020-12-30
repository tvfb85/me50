import Foundation

struct PokemonListResults: Codable {
    let results: [PokemonListResult]
}

struct PokemonListResult: Codable {
    let name: String
    let url: String
}

struct PokemonResult: Codable {
    let id: Int
    let name: String
    let types: [PokemonTypeEntry]
    let sprites: Sprite
}

struct Sprite: Codable {
    let front_default: String
}

struct PokemonTypeEntry: Codable {
    let slot: Int
    let type: PokemonType
}

struct PokemonType: Codable {
    let name: String
}

struct PokemonCaught: Codable {
    var state = [String : Bool]()
}

struct PokemonInfo: Codable {
    let flavor_text_entries: [FlavorText]
}

struct FlavorText: Codable {
    let flavor_text: String
    let language: LanguageEntry
}

struct LanguageEntry: Codable {
    let name: String
}

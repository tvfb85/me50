import UIKit

var pokemoncaught = PokemonCaught.init(state: [ : ])

class PokemonViewController: UIViewController {
    var url: String!
    var isCaught = false

    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var imageView: UIImageView!
    @IBOutlet var descriptionText: UITextView!

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""
        descriptionText.text = ""

        loadPokemon()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                DispatchQueue.main.async {
                    print(result)
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.setLabels(pokemon: result)
                    self.loadImage(imageUrl: result.sprites.front_default)
                    self.loadDescription(pokemonId: result.id)
                    self.setCaughtState(name: self.nameLabel.text!)
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
    
    func setLabels(pokemon: PokemonResult) {
        nameLabel.text = capitalize(text: pokemon.name)
        numberLabel.text = String(format: "#%03d", pokemon.id)
        
        for typeEntry in pokemon.types {
            if typeEntry.slot == 1 {
                type1Label.text = typeEntry.type.name
            }
            else if typeEntry.slot == 2 {
                type2Label.text = typeEntry.type.name
            }
        }
    }
    
    func loadImage(imageUrl: String) {
        guard let url = URL(string: imageUrl) else {
            return
        }
        
        do {
            let data = try Data(contentsOf: url)
            let image = UIImage(data: data)
            imageView.image = image
        }
        catch let error {
            print("Error reading image url: \(error)")
        }
    }
    
    func loadDescription(pokemonId: Int) {
        guard let requestUrl = URL(string: "https://pokeapi.co/api/v2/pokemon-species/\(pokemonId)") else {
            return
        }
        
        URLSession.shared.dataTask(with: requestUrl) { (data, response, error) in
            guard let data = data else {
                return
            }
            
            do {
                let pokemonInfo = try JSONDecoder().decode(PokemonInfo.self, from: data)
                DispatchQueue.main.async {
                    for entry in pokemonInfo.flavor_text_entries {
                        if entry.language.name == "en" {
                            self.descriptionText.text = entry.flavor_text
                            break
                        }
                    }
                }
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
    
    func setCaughtState(name: String) {
        if UserDefaults.standard.bool(forKey: name) == true {
            pokemoncaught.state[name] = true
        }
        if pokemoncaught.state[name] == nil || pokemoncaught.state[name] == false {
            catchButton.setTitle("Catch!", for: .normal)
        }
        else {
            catchButton.setTitle("Release", for: .normal)
        }
    }
    
    @IBAction func toggleCatch() {
        
        if pokemoncaught.state[nameLabel.text!] == nil || pokemoncaught.state[nameLabel.text!] == false {
            catchButton.setTitle("Release", for: .normal)
            pokemoncaught.state[nameLabel.text!] = true
            UserDefaults.standard.set(true, forKey: nameLabel.text!)
        }
        else {
            catchButton.setTitle("Catch!", for: .normal)
            pokemoncaught.state[nameLabel.text!] = false
            UserDefaults.standard.set(false, forKey: nameLabel.text!)
        }
        
    }

}

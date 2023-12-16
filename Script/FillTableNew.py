import unreal

# Chemin de la DataTable dans l'éditeur
data_table_path = '/Game/TestFlag.TestFlag'

# Chemin du dossier contenant les textures
texture_directory_path = '/Game/Flags'
s_flag_struct = unreal.load_asset("/Game/S_flag")
print(type(s_flag_struct))


# Récupérer la DataTable
data_table = unreal.load_asset(data_table_path)

# Vérifier si la DataTable existe
if data_table is None:
    unreal.log("La DataTable n'existe pas.")
else:
    # Récupérer toutes les textures dans le dossier spécifié
    texture_assets = unreal.EditorAssetLibrary.list_assets(texture_directory_path)
    
    # Parcourir la liste des textures et ajouter les lignes à la DataTable
    for texture_path in texture_assets:
        texture = unreal.load_asset(texture_path)
        country_code = unreal.SystemLibrary.get_object_name(texture)
        print(country_code)

        # Créer une nouvelle ligne pour la DataTable (change "CountryFlagStructure" par le nom de ta structure)
        new_row = {'CountryCode': country_code, 'FlagTexture': texture}
                
        # Ajouter la nouvelle ligne à la DataTable
        data_table.add_row(country_code, new_row)

    unreal.log("DataTable rempli avec succès.")

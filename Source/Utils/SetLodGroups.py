#
# Looks at all static meshes in a map and makes sure they have their LOD group set.
#
import unreal

actors = unreal.EditorLevelLibrary.get_all_level_actors()
actorComponents = unreal.EditorLevelLibrary.get_all_level_actors_components()

if len(actors) == 0 and len(actorComponents) == 0:
    print("No actors")
    exit(-2)

NumFixed = 0
with unreal.ScopedEditorTransaction("Set Missing LOD Groups") as trans:
    for actor in actors:
        if actor and actor.get_class() == unreal.StaticMeshActor.static_class():
            sm = actor.static_mesh_component.static_mesh
			
            if sm:
                if sm.get_editor_property("lod_group").is_none():
                    bounds = sm.get_bounds()
                    
                    #Small/large radius threshold is 300, somewhat arbitrary
                    is_large = bounds.sphere_radius > 300.0
                    lod_group = "LargeProp" if is_large  else "SmallProp"
                    
                    sm.set_editor_property("lod_group", lod_group)
                    unreal.EditorAssetLibrary.save_loaded_asset(sm)
                    NumFixed += 1
                    print("LOD SM group " + str(lod_group) + " to " + str(actor))

    for actorComponent in actorComponents:
        if actorComponent and actorComponent.get_class() == unreal.StaticMeshComponent.static_class():
            sm = actorComponent.static_mesh
			
            if sm:
                if sm.get_editor_property("lod_group").is_none():
                    bounds = sm.get_bounds()
                    
                    #Small/large radius threshold is 300, somewhat arbitrary
                    is_large = bounds.sphere_radius > 300.0
                    lod_group = "LargeProp" if is_large  else "SmallProp"
                    
                    sm.set_editor_property("lod_group", lod_group)
                    unreal.EditorAssetLibrary.save_loaded_asset(sm)
                    NumFixed += 1
                    print("LOD SMC group " + str(lod_group) + " to " + str(actorComponent))

print("Set LOD group for " + str(NumFixed) + " static meshes")
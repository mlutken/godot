def can_build(env, platform):
    return not env["disable_3d"]


def configure(env):
    pass


def get_doc_classes():
    return [
        "EditorSceneImporterGLTF",
        "GLTFAccessor",
        "GLTFAnimation",
        "GLTFBufferView",
        "GLTFCamera",
        "GLTFDocument",
        "GLTFLight",
        "GLTFMesh",
        "GLTFNode",
        "GLTFSkeleton",
        "GLTFSkin",
        "GLTFSpecGloss",
        "GLTFState",
        "GLTFTexture",
        "GLTFDocumentExtension",
        "GLTFDocumentExtensionConvertImporterMesh",
    ]


def get_doc_path():
    return "doc_classes"

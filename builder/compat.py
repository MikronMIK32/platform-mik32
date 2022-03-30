from SCons.Script import AlwaysBuild, Import

Import("env")

# Added in PIO Core 4.4.0
if not hasattr(env, "AddPlatformTarget"):

    def AddPlatformTarget(
        env,
        name,
        dependencies,
        actions,
        title=None,
        description=None,
        always_build=True,
    ):
        target = env.Alias(name, dependencies, actions)
        if always_build:
            AlwaysBuild(target)
        return target

    env.AddMethod(AddPlatformTarget)
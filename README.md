SlackEngine 顾名思义是在空余的时候(moyu) 写的。
            主旨在于学习Vulkan API的一些特性以及使用手法

在Docs的Vulkan notes 中详细记录了本次的学习过程。

一些重要的external：
       assimp :加载obj
       reactphysics: 物理引擎
       openal: 音频
       VulkanSDK: 把vulkan-1.dll 放到了lib里面，保证使用版本为1.3


限制：
    和以前学习Opengl或者dx一样，因为工作中很少能使用到，一般学习一段时间后都会生疏忘记。
    故而一开始所展望的一些功能，以及RHI多图形库封装都没实现(因为实现的时候都忍不住想去看ue是怎么做的，实现得越来越ue化，那还不如不实现了，好好读读ue源码)
    一开始用的cmake 来对代码做管理，后面发现对于这个项目投入的精力做不了太多，干脆怎么方便怎么来



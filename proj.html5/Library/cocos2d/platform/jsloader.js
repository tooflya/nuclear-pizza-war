/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

 http://www.cocos2d-x.org


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
(function () {
    var engine = [
        'platform/CCClass.js',
        'cocoa/CCGeometry.js',
        'platform/Sys.js',
        'platform/CCConfig.js',
        'platform/miniFramework.js',
        'platform/CCCommon.js',
        'platform/ZipUtils.js',
        'platform/base64.js',
        'platform/gzip.js',
        'platform/CCMacro.js',
        'platform/CCFileUtils.js',
        'platform/CCTypes.js',
        'platform/CCAccelerometer.js',
        'platform/zlib.min.js',
        'platform/CCEGLView.js',
        'platform/CCImage.js',
        'kazmath/utility.js',
        'kazmath/vec2.js',
        'kazmath/vec3.js',
        'kazmath/vec4.js',
        'kazmath/ray2.js',
        'kazmath/mat3.js',
        'kazmath/mat4.js',
        'kazmath/plane.js',
        'kazmath/quaternion.js',
        'kazmath/aabb.js',
        'kazmath/GL/mat4stack.js',
        'kazmath/GL/matrix.js',
        'cocoa/CCSet.js',
        'cocoa/CCNS.js',
        'cocoa/CCAffineTransform.js',
        'support/CCPointExtension.js',
        'support/CCUserDefault.js',
        'support/CCVertex.js',
        'support/TransformUtils.js',
        'support/CCTGAlib.js',
        'support/CCPNGReader.js',
        'support/CCTIFFReader.js',
        'support/component/CCComponent.js',
        'support/component/CCComponentContainer.js',
        'shaders/CCShaders.js',
        'shaders/CCShaderCache.js',
        'shaders/CCGLProgram.js',
        'shaders/CCGLStateCache.js',
        'base_nodes/CCNode.js',
        'base_nodes/CCAtlasNode.js',
        'textures/CCTexture2D.js',
        'textures/CCTextureCache.js',
        'textures/CCTextureAtlas.js',
        'misc_nodes/CCRenderTexture.js',
        'misc_nodes/CCProgressTimer.js',
        'misc_nodes/CCMotionStreak.js',
        'misc_nodes/CCClippingNode.js',
        'effects/CCGrid.js',
        'effects/CCGrabber.js',
        'draw_nodes/CCDrawNode.js',
        'actions/CCAction.js',
        'actions/CCActionInterval.js',
        'actions/CCActionInstant.js',
        'actions/CCActionManager.js',
        'actions/CCActionProgressTimer.js',
        'actions/CCActionCamera.js',
        'actions/CCActionEase.js',
        'actions/CCActionGrid.js',
        'actions/CCActionGrid3D.js',
        'actions/CCActionTiledGrid.js',
        'actions/CCActionCatmullRom.js',
        'actions/CCActionPageTurn3D.js',
        'actions/CCActionTween.js',
        'layers_scenes_transitions_nodes/CCScene.js',
        'layers_scenes_transitions_nodes/CCLayer.js',
        'layers_scenes_transitions_nodes/CCTransition.js',
        'layers_scenes_transitions_nodes/CCTransitionProgress.js',
        'layers_scenes_transitions_nodes/CCTransitionPageTurn.js',
        'sprite_nodes/CCSprite.js',
        'sprite_nodes/CCAnimation.js',
        'sprite_nodes/CCAnimationCache.js',
        'sprite_nodes/CCSpriteFrame.js',
        'sprite_nodes/CCSpriteFrameCache.js',
        'sprite_nodes/CCSpriteBatchNode.js',
        'label_nodes/CCLabelAtlas.js',
        'label_nodes/CCLabelTTF.js',
        'label_nodes/CCLabelBMFont.js',
        'particle_nodes/CCParticleSystem.js',
        'particle_nodes/CCParticleExamples.js',
        'particle_nodes/CCParticleBatchNode.js',
        'touch_dispatcher/CCTouchDelegateProtocol.js',
        'touch_dispatcher/CCTouchHandler.js',
        'touch_dispatcher/CCTouchDispatcher.js',
        'touch_dispatcher/CCMouseDispatcher.js',
        'keyboard_dispatcher/CCKeyboardDelegate.js',
        'keyboard_dispatcher/CCKeyboardDispatcher.js',
        'text_input_node/CCIMEDispatcher.js',
        'text_input_node/CCTextFieldTTF.js',
        'CCConfiguration.js',
        'CCDirector.js',
        'CCCamera.js',
        'CCScheduler.js',
        'CCLoader.js',
        'CCDrawingPrimitives.js',
        'platform/CCApplication.js',
        'platform/CCSAXParser.js',
        'platform/AppControl.js',
        'menu_nodes/CCMenuItem.js',
        'menu_nodes/CCMenu.js',
        'tileMap_parallax_nodes/CCTMXTiledMap.js',
        'tileMap_parallax_nodes/CCTMXXMLParser.js',
        'tileMap_parallax_nodes/CCTMXObjectGroup.js',
        'tileMap_parallax_nodes/CCTMXLayer.js',
        'tileMap_parallax_nodes/CCParallaxNode.js',
        'base_nodes/CCdomNode.js',
        '../CocosDenshion/SimpleAudioEngine.js'
    ];

    var d = document;
    var c = d["ccConfig"];

    if (c.loadExtension != null && c.loadExtension == true) {
        engine = engine.concat([
            '../extensions/GUI/CCControlExtension/CCControl.js',
            '../extensions/GUI/CCControlExtension/CCControlButton.js',
            '../extensions/GUI/CCControlExtension/CCControlUtils.js',
            '../extensions/GUI/CCControlExtension/CCInvocation.js',
            '../extensions/GUI/CCControlExtension/CCScale9Sprite.js',
            '../extensions/GUI/CCControlExtension/CCMenuPassive.js',
            '../extensions/GUI/CCControlExtension/CCControlSaturationBrightnessPicker.js',
            '../extensions/GUI/CCControlExtension/CCControlHuePicker.js',
            '../extensions/GUI/CCControlExtension/CCControlColourPicker.js',
            '../extensions/GUI/CCControlExtension/CCControlSlider.js',
            '../extensions/GUI/CCControlExtension/CCControlSwitch.js',
            '../extensions/GUI/CCControlExtension/CCControlStepper.js',
            '../extensions/GUI/CCControlExtension/CCControlPotentiometer.js',
            '../extensions/GUI/CCScrollView/CCScrollView.js',
            '../extensions/GUI/CCScrollView/CCSorting.js',
            '../extensions/GUI/CCScrollView/CCTableView.js',
            '../extensions/CCBReader/CCNodeLoader.js',
            '../extensions/CCBReader/CCBReaderUtil.js',
            '../extensions/CCBReader/CCControlLoader.js',
            '../extensions/CCBReader/CCSpriteLoader.js',
            '../extensions/CCBReader/CCNodeLoaderLibrary.js',
            '../extensions/CCBReader/CCBReader.js',
            '../extensions/CCBReader/CCBValue.js',
            '../extensions/CCBReader/CCBKeyframe.js',
            '../extensions/CCBReader/CCBSequence.js',
            '../extensions/CCBReader/CCBRelativePositioning.js',
            '../extensions/CCBReader/CCBAnimationManager.js',
            '../extensions/CCEditBox.js',
            '../extensions/CocoStudio/Armature/utils/CCArmatureDefine.js',
            '../extensions/CocoStudio/Armature/utils/CCDataReaderHelper.js',
            '../extensions/CocoStudio/Armature/utils/CCSpriteFrameCacheHelper.js',
            '../extensions/CocoStudio/Armature/utils/CCTransformHelp.js',
            '../extensions/CocoStudio/Armature/utils/CCTweenFunction.js',
            '../extensions/CocoStudio/Armature/utils/CCUtilMath.js',
            '../extensions/CocoStudio/Armature/utils/CSArmatureDataManager.js',
            '../extensions/CocoStudio/Armature/datas/CCDatas.js',
            '../extensions/CocoStudio/Armature/display/CCBatchNode.js',
            '../extensions/CocoStudio/Armature/display/CCDecorativeDisplay.js',
            '../extensions/CocoStudio/Armature/display/CCDisplayFactory.js',
            '../extensions/CocoStudio/Armature/display/CCDisplayManager.js',
            '../extensions/CocoStudio/Armature/display/CCSkin.js',
            '../extensions/CocoStudio/Armature/animation/CCProcessBase.js',
            '../extensions/CocoStudio/Armature/animation/CCArmatureAnimation.js',
            '../extensions/CocoStudio/Armature/animation/CCTween.js',
            '../extensions/CocoStudio/Armature/physics/CCColliderDetector.js',
            '../extensions/CocoStudio/Armature/CCArmature.js',
            '../extensions/CocoStudio/Armature/CCBone.js'

        ]);
    }

    if (c.loadPluginx != null && c.loadPluginx == true) {
        engine = engine.concat([
            //protocols
            '../extensions/PluginX/protocols/Config.js',
            '../extensions/PluginX/protocols/PluginUtils.js',
            '../extensions/PluginX/protocols/PluginProtocol.js',
            '../extensions/PluginX/protocols/ProtocolSocial.js',
            //'../extensions/PluginX/protocols/ProtocolAds.js',
            //'../extensions/PluginX/protocols/ProtocolAnalytics.js',
            //'../extensions/PluginX/protocols/ProtocolIAP.js',
            '../extensions/PluginX/protocols/PluginFactory.js',
            '../extensions/PluginX/protocols/PluginManager.js',

            //plugins
            '../extensions/PluginX/plugins/SocialWeibo.js',
            '../extensions/PluginX/plugins/SocialQQWeibo.js',
            '../extensions/PluginX/plugins/SocialQzone.js',
            '../extensions/PluginX/plugins/SocialTwitter.js',
            '../extensions/PluginX/plugins/SocialFacebook.js'
            //'../extensions/PluginX/plugins/AdsGoogle.js'
        ]);
    }

    if (!c.engineDir) {
        engine = [];
    }
    else {
        if(c.box2d || c.chipmunk){
            engine.push('physics_nodes/CCPhysicsSprite.js');
            engine.push('physics_nodes/CCPhysicsDebugNode.js');
            if (c.box2d === true)
                engine.push('../box2d/box2d.js');
            if (c.chipmunk === true)
                engine.push('../chipmunk/chipmunk.js');
        }
        engine.forEach(function (e, i) {
            engine[i] = c.engineDir + e;
        });
        if(typeof c.box2d === "string")
        {
            engine.push(c.box2d);
        }
        if(typeof c.chipmunk === "string")
        {
            engine.push(c.chipmunk);
        }

    }

    var loadJsImg = document.getElementById("cocos2d_loadJsImg");
    if(!loadJsImg){
        loadJsImg = new Image();
        loadJsImg.src = "data:image/gif;base64,R0lGODlhQAFAAfcAAP///wFRqsbX64Sq1bbM5pq53DZ1u1aLxtjk8eTs9bzR6B5lswRTqwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACH/C05FVFNDQVBFMi4wAwEAAAAh+QQJCgAAACwAAAAAQAFAAQAI/wABCBxIsKDBgwgTKlzIsKHDhxAjSpxIsaLFixgzatzIsaPHjyBDihxJsqTJkyhTqlzJsqXLlzBjypxJs6bNmzhz6tzJs6fPn0CDCh1KtKjRo0iTKl3KtKnTp1CjSp1KtarVq1izat3KtavXr2DDih1LtqzZs2jTql3Ltq3bt3Djyp1Lt67du3jz6t3Lt6/fv4ADCx5MuLDhw4gTK17MuLHjx5AjS55MubLly5gza97MubPnz6BDix5NurTp06hTq17NurXr17Bjy55Nu7bt27hz697Nu7fv38CDCx9OvLjx48iTK1/OvLnz59CjS59Ovbr169iza9/Ovbv37+DDi/8fT768+fPo06tfz769+/fw48ufT7++/fv48+vfz7+///8ABijggAQWaOCBCCao4IIMNujggxBGKOGEFFZo4YUYZqjhhhx26OGHIIYo4ogklmjiiSimqOKKLLbo4ou2FcBAATA2tAADCxSEQAIvEjBAQQwESZAABBDgYgILLHAAQUEyMFACRSrwYpILGClQkwMpUCQCLw6QpAEDYQkAAlHWaECSPwIgZpEE8AgjAVTyiCWZBAhAEJ1uhkiAAQbQONABaBoE5ZNabjliAXwacICVAizgZ0JEsmkniQckqiiXDLFJgAJ5kkhApYk2RCemKSJqgJUMkbpiAmnW2JGmUXb/yqEABQxg660QwVrmh7f22mpDunIKIq2+/uqqRqqumGxCoyprKEOFbiqriAlEK2VDkRY56YjZbroQmYSyuWyHdEo7UJsG0bntmFpO2yGUBKgaKZdsCsSmuyrCa2W9Y+76YqGY8gsAwC/SeS0AAuv7b5F5CgxApD3WSZDDY+J7YgLJannwsQdVazHHIIcs8sgkl2zyySinrPLKLLfs8sswxyzzzDTXbPPNOOes88489+zzz0AHLfTQRBdt9NFIJ6300kw37fTTUEct9dRUV2311VhnrfXWXHft9ddghy322GSXbfbZaKet9tpst+3223DHLffcdNdt991456333nz3KO3334AHLvjghBdu+OGIJ6744ow37vjjkEcu+eSUV2755ZhnrrnhAQEAIfkECQoAAAAsAAAAAEABQAEACP8AAQgcSLCgwYMIEypcyLChw4cQI0qcSLGixYsYM2rcyLGjx48gQ4ocSbKkyZMoU6pcybKly5cwY8qcSbOmzZs4c+rcybOnz59AgwodSrSo0aNIkypdyrSp06dQo0qdSrWq1atYs2rdyrWr169gw4odS7as2bNo06pdy7at27dw48qdS7eu3bt48+rdy7ev37+AAwseTLiw4cOIEytezLix48eQI0ueTLmy5cuYM2vezLmz58+gQ4seTbq06dOoU6tezbq169ewY8ueTbu27du4c+vezbu379/AgwsfTry48ePIkytfzry58+fQo0ufTr269evYs2vfzr279+/gw4v/H0++vPnz6NOrX8++vfv38OPLn0+/vv37+PPr38+/v///AAYo4IAEFmjggQgmqOCCDDbo4IMQRijhhBRWaOGFGGao4YYcdujhhyCGKOKIJJZo4okopqjiiiy26OKLthWwAAEwNmTAAgYUNEABLxLAI0ELBEmQAQww4GICBhhwAJBCClRAkQu8mKQBCgwUZJQCLVDkAC8WkOSSWTY5AJQ1HpDkj1cCgECRDPzY45QJAJDmAUXmOBACBBAQp4gIDDBAlQOZaQCXBT0pgEAJKJAnAQiMqICffjaqpgE0KiTAogQcSiIBkO6450KYKvApiX122hCejK746ACaMiQpiwlU/1pjR5jmKSqIidYqa0O6EgCoh4rqCpGut36Ya62zevQqi8sqhGqzJj7bULC+jjrisb46dOmirYq4bZ7dHoTnQNhC2yGq1Q6kp0GodouAotZ6GGuqA23b6KICLRrvivNWiq+attYYrKT/AjDwi6j+WnC/Lwb7acEAbNtjpgRBrOa+KCbQrKK/JntQohh7LPLIJJds8skop6zyyiy37PLLMMcs88w012zzzTjnrPPOPPfs889ABy300EQXbfTRSCet9NJMN+3001BHLfXUVFdt9dVYZ6311lx37fXXYIct9thkl2322WinrfbabLft9ttwxy333HTXbffdeOet99589yrt99+ABy744IQXbvjhiCeu+OKMN+7445BHLvnklFdu+eWYZ6755pwnHhAAIfkECQoAAAAsAAAAAEABQAEACP8AAQgcSLCgwYMIEypcyLChw4cQI0qcSLGixYsYM2rcyLGjx48gQ4ocSbKkyZMoU6pcybKly5cwY8qcSbOmzZs4c+rcybOnz59AgwodSrSo0aNIkypdyrSp06dQo0qdSrWq1atYs2rdyrWr169gw4odS7as2bNo06pdy7at27dw48qdS7eu3bt48+rdy7ev37+AAwseTLiw4cOIEytezLix48eQI0ueTLmy5cuYM2vezLmz58+gQ4seTbq06dOoU6tezbq169ewY8ueTbu27du4c+vezbu379/AgwsfTry48ePIkytfzry58+fQo0ufTr269evYs2vfzr279+/gw4v/H0++vPnz6NOrX8++vfv38OPLn0+/vv37+PPr38+/v///AAYo4IAEFmjggQgmqOCCDDbo4IMQRijhhBRWaOGFGGao4YYcdujhhyCGKOKIJJZo4okopqjiiiy26OKLthFgAAEwNnSAAQcUNACNLiKgQEEGBEnQAQss4GICA+xIUJAGDERAkU26mOQACAzEpJVFDvCiAlNaKSQAA0BZYwFJ/gjAlQkUuQCPAyWwIgJTunllmAvkONAADDBQwIgJEKBAlQORqWRBBSwggECF5smAliIiQMCjCrgJAJKHJiSAAYoyEOWIAjz6qACSLpTpmicmoICnZi6E56JvPgooQwe8/6piArLWuJGnqIbaoam4PgpRr5CCeCqwv/YaKYi89mqrR7Wq2CxCjhLwLInRTlvQsH7qyie2qS7UqaeVcopruNCymay0I0abrZPaAhAtuT4S0O6urhL0bZWeCuTpvLPmC4C/0Xbb4rCA+gsAwS8G7KSvAvXJ8MCPhmowAN+++ClBE7vLb6m1nirwsgWZujHIJJds8skop6zyyiy37PLLMMcs88w012zzzTjnrPPOPPfs889ABy300EQXbfTRSCet9NJMN+3001BHLfXUVFdt9dVYZ6311lx37fXXYIct9thkl2322WinrfbabLft9ttwxy333HTXbffdeOet99589y3t99+ABy744IQXbvjhiCeu+OKMN+7445BHLvnklFdu+eWYZ6755px37rniAQEAIfkECQoAAAAsAAAAAEABQAEACP8AAQgcSLCgwYMIEypcyLChw4cQI0qcSLGixYsYM2rcyLGjx48gQ4ocSbKkyZMoU6pcybKly5cwY8qcSbOmzZs4c+rcybOnz59AgwodSrSo0aNIkypdyrSp06dQo0qdSrWq1atYs2rdyrWr169gw4odS7as2bNo06pdy7at27dw48qdS7eu3bt48+rdy7ev37+AAwseTLiw4cOIEytezLix48eQI0ueTLmy5cuYM2vezLmz58+gQ4seTbq06dOoU6tezbq169ewY8ueTbu27du4c+vezbu379/AgwsfTry48ePIkytfzry58+fQo0ufTr269evYs2vfzr279+/gw4v/H0++vPnz6NOrX8++vfv38OPLn0+/vv37+PPr38+/v///AAYo4IAEFmjggQgmqOCCDDbo4IMQRijhhBRWaOGFGGao4YYcdujhhyCGKOKIJJZo4okopqjiiiy26OKLtgkwgAAwNlTAAAUUVAABLyaAQEEDBEnQAQYY4GICBBBA40BBDjAQAUUa6WKSBCTApJACEWlAji4ikKQCVzoJQAFFHlCjAkn+CECTACQQJY8EWakikklayeYAZRI0wAILwBkikgqoKZAAaRoEpZpQ8rmAmCF6+aWcSAp6kAAHKLqAmSQSSqUAci5kqQF+kpgAmlTayCejKDoqqUIDdDrnqjVq/8TArLQuwKWHo1JZ6kO09soAiKTqGipDvjJgK4i5ChurR7Cm2OxBqq4YLUPBKuDqiMkSAGZDmia55IjdKrmQlwNl++yGjmrbaZUGOfotAAigeS2uhQ6k6Y+7UjnvinTCuauj275IKqJJDjTwiwA/WbBA/Qpcp8KhavqitwTtOhAC+6LoY0FoBrzsQaNm/PHIJJds8skop6zyyiy37PLLMMcs88w012zzzTjnrPPOPPfs889ABy300EQXbfTRSCet9NJMN+3001BHLfXUVFdt9dVYZ6311lx37fXXYIct9thkl2322WinrfbabLft9ttwxy333HTXbffdeOet99589yvt99+ABy744IQXbvjhiCeu+OKMN+7445BHLvnklFdu+eWYZ6755px3rnhAACH5BAkKAAAALAAAAABAAUABAAj/AAEIHEiwoMGDCBMqXMiwocOHECNKnEixosWLGDNq3Mixo8ePIEOKHEmypMmTKFOqXMmypcuXMGPKnEmzps2bOHPq3Mmzp8+fQIMKHUq0qNGjSJMqXcq0qdOnUKNKnUq1qtWrWLNq3cq1q9evYMOKHUu2rNmzaNOqXcu2rdu3cOPKnUu3rt27ePPq3cu3r9+/gAMLHky4sOHDiBMrXsy4sePHkCNLnky5suXLmDNr3sy5s+fPoEOLHk26tOnTqFOrXs26tevXsGPLnk27tu3buHPr3s27t+/fwIMLH068uPHjyJMrX868ufPn0KNLn069uvXr2LNr3869u/fv4MOL/x9Pvrz58+jTq1/Pvr379/Djy59Pv779+/jz69/Pv7///wAGKOCABBZo4IEIJqjgggw26OCDEEYo4YQUVmjhhRhmqOGGHHbo4YcghijiiCSWaOKJKKao4oostujii7YhUAACMDZEQAEFFKQAjS4mwONAOOYI5AAD9EgAAQIQFORACBBZpItHEpAAkDgO5KQCLyJwJJYCLQmAAk7WqMCRPC6ZgJM/CjSliglEOeWSBBApZJcGGEDAiG3uSJAAZBokwABrEnBAnQbMCaKWW67ZZpoGITAooQeUyGeUAqy5EKEGHMBliQmMGWVDBdRp6ImIMpoQoC36WONHC7TqaqEgdv8a5acPuWrrAiB6Ouudtd5qZ6y60roqRwOYiqKxBw3AAANPplhqQ8suu8CoIsq6ZUMCGBAtAwZIOmuSCmkJ5ALRNntolApYKmWjR4IrkLIM8BpimwSkOSmNtLpZI7280oropi56yqOwAmd5rUDC8vuip+oeuafDUCJJkLACIWApi6oSNCbAwxrU6cUdhyzyyCSXbPLJKKes8sost+zyyzDHLPPMNNds880456zzzjz37PPPQAct9NBEF2300UgnrfTSTDft9NNQRy311FRXbfXVWGet9dZcd+3112CHLfbYZJdt9tlop6322my37fbbcMct99x012333XjnrffefPcp7fffgAcu+OCEF2744YgnrvjijDfu+OOQRy755JRXbvnlmGeu+eaMBwQAIfkECQoAAAAsAAAAAEABQAEACP8AAQgcSLCgwYMIEypcyLChw4cQI0qcSLGixYsYM2rcyLGjx48gQ4ocSbKkyZMoU6pcybKly5cwY8qcSbOmzZs4c+rcybOnz59AgwodSrSo0aNIkypdyrSp06dQo0qdSrWq1atYs2rdyrWr169gw4odS7as2bNo06pdy7at27dw48qdS7eu3bt48+rdy7ev37+AAwseTLiw4cOIEytezLix48eQI0ueTLmy5cuYM2vezLmz58+gQ4seTbq06dOoU6tezbq169ewY8ueTbu27du4c+vezbu379/AgwsfTry48ePIkytfzry58+fQo0ufTr269evYs2vfzr279+/gw4v/H0++vPnz6NOrX8++vfv38OPLn0+/vv37+PPr38+/v///AAYo4IAEFmjggQgmqOCCDDbo4IMQRijhhBRWaOGFGGao4YYcdujhhyCGKOKIJJZo4okopqjiiiy26OKLtiWgQAIwNqQAAQoUJAACLybAI0EEBAlkAQW4mECQAgAppEAIEEnAi0ESQKNAUQ5EAJFJuohAkDlSuaQARBYJ440E/FhlAmH+ONCUKR4ZJI1VglnAkwMpMMAAaoJ4pAJ5ChBknkxKyeSdd3YZ4pZcTnkkoAWhSegAYo7oZ5QCsKnQo3ieKGOUdC4kQKErIsooQoKy6GONHxmg6qoHdNrhppy6/8rQqrQaACKZsUJUqwGt6olrlah2NIClKo56UAELLDBAqH82lGyyBsgqIqw4NoTAAc8ucECJkyK50AAMZEmAAc8uKyKiOLJZKkEHMMCArQMNQK60rzY70KQ8nukuA5EaCSyw4DKwQI1kmrkkAAu4a26LiBoKLAAE7PsimeoeDIAB7hKbordWWgwApD0CeqOhwR4ko8Ylp6zyyiy37PLLMMcs88w012zzzTjnrPPOPPfs889ABy300EQXbfTRSCet9NJMN+3001BHLfXUVFdt9dVYZ6311lx37fXXYIct9thkl2322WinrfbabLft9ttwxy333HTXbffdeOet99589zPt99+ABy744IQXbvjhiCeu+OKMN+7445BHLvnklFdu+eWYZ6755px37vnnoIcu+uiSBwQAIfkECQoAAAAsAAAAAEABQAEACP8AAQgcSLCgwYMIEypcyLChw4cQI0qcSLGixYsYM2rcyLGjx48gQ4ocSbKkyZMoU6pcybKly5cwY8qcSbOmzZs4c+rcybOnz59AgwodSrSo0aNIkypdyrSp06dQo0qdSrWq1atYs2rdyrWr169gw4odS7as2bNo06pdy7at27dw48qdS7eu3bt48+rdy7ev37+AAwseTLiw4cOIEytezLix48eQI0ueTLmy5cuYM2vezLmz58+gQ4seTbq06dOoU6tezbq169ewY8ueTbu27du4c+vezbu379/AgwsfTry48ePIkytfzry58+fQo0ufTr269evYs2vfzr279+/gw4v/H0++vPnz6NOrX8++vfv38OPLn0+/vv37+PPr38+/v///AAYo4IAEFmjggQgmqOCCDDbo4IMQRijhhBRWaOGFGGao4YYcdujhhyCGKOKIJJZo4okopqjiiiy26OKLtiWgQAIwNqQAAQoUhACNLiaAQEEEBEmQAEK2mECQAhAUJAEDHYnji0vyCMCSA91IwI8uIhBkjgJRCYCWT8JoJZZUOkmAlAKheaKZNFIJZpIDgammh0cqgKVARF5p0JE8yrjknSCCiWOfeiaUQJ5IlogoAQLMedCSg65pZZELgQnoiZY6tKORl9ao0QCghloAnHRO6qVDoaY6AIimntqQqgOM/wqin5Ay6WlHAziKqUMEGGBAAStmypCvvh5ga4m0hlnpAcQacICikJKKUAELwEkAs74CK6KgMw50pkEDLLDAswMV4OuxswYJaJ4/MuAuAAmIuwC6RnrpLgMChbuAATWOKdC9Axkg7qpZbjkQwF3K+6KVUiIs0AHi6mpioge/S9AA9KroY0ELMLDArQoVwIC2IJds8skop6zyyiy37PLLMMcs88w012zzzTjnrPPOPPfs889ABy300EQXbfTRSCet9NJMN+3001BHLfXUVFdt9dVYZ6311lx37fXXYIct9thkl2322WinrfbabLft9ttwxy333HTXbffdeOet99589y7t99+ABy744IQXbvjhiCeu+OKMN+7445BHLvnklFdu+eWYZ6755px37vnnkgcEACH5BAkKAAAALAAAAABAAUABAAj/AAEIHEiwoMGDCBMqXMiwocOHECNKnEixosWLGDNq3Mixo8ePIEOKHEmypMmTKFOqXMmypcuXMGPKnEmzps2bOHPq3Mmzp8+fQIMKHUq0qNGjSJMqXcq0qdOnUKNKnUq1qtWrWLNq3cq1q9evYMOKHUu2rNmzaNOqXcu2rdu3cOPKnUu3rt27ePPq3cu3r9+/gAMLHky4sOHDiBMrXsy4sePHkCNLnky5suXLmDNr3sy5s+fPoEOLHk26tOnTqFOrXs26tevXsGPLnk27tu3buHPr3s27t+/fwIMLH068uPHjyJMrX868ufPn0KNLn069uvXr2LNr3869u/fv4MOL/x9Pvrz58+jTq1/Pvr379/Djy59Pv779+/jz69/Pv7///wAGKOCABBZo4IEIJqjgggw26OCDEEYo4YQUVmjhhRhmqOGGHHbo4YcghijiiCSWaOKJKKao4oostujii7YloEACMDakAAEKFIQAjS4mgEBBBARJkABCtphAkAIQFCQBAx2J44tL8gjAkgPdSMCPLiIQZI4CUQmAlk/CaCWWVDpJgJQCoXmimTRSCWaSA4GppodHKoClQEReadCRPMq45J0ggoljn3omlECeSJaIKAECzHnQkoOuaWWRC4EJ6ImWOrSjkZfWqBGkWzqaoZ+gQgTqliBOCqmpoM4IIqmrev/a0ZlZOiTAAANwmWKmDOHqa6chwqqrQgkU4OsABSgKKZwJEWAAlggcO+yHgroKgAAMDGDQAAYYcABBCuAKLIdOAmoAAwx8u8C6ACTQrQFMwlgAugzQuO4CAhXQ7bcwLoCutgDcO9AB3Sbr4gDo4iuQwF2++6K/DBgcMLsDdyuqiegaQBDDAxUQb4vGFmTAAhrL2uwCEpus8sost+zyyzDHLPPMNNds880456zzzjz37PPPQAct9NBEF2300UgnrfTSTDft9NNQRy311FRXbfXVWGet9dZcd+3112CHLfbYZJdt9tlop6322my37fbbcMct99x012333XjnrffefPc07fffgAcu+OCEF2744YgnrvjijDfu+OOQRy755JRXbvnlmGeu+eacd+7556CHLvropFseEAAh+QQJCgAAACwAAAAAQAFAAQAI/wABCBxIsKDBgwgTKlzIsKHDhxAjSpxIsaLFixgzatzIsaPHjyBDihxJsqTJkyhTqlzJsqXLlzBjypxJs6bNmzhz6tzJs6fPn0CDCh1KtKjRo0iTKl3KtKnTp1CjSp1KtarVq1izat3KtavXr2DDih1LtqzZs2jTql3Ltq3bt3Djyp1Lt67du3jz6t3Lt6/fv4ADCx5MuLDhw4gTK17MuLHjx5AjS55MubLly5gza97MubPnz6BDix5NurTp06hTq17NurXr17Bjy55Nu7bt27hz697Nu7fv38CDCx9OvLjx48iTK1/OvLnz59CjS59Ovbr169iza9/Ovbv37+DDi/8fT768+fPo06tfz769+/fw48ufT7++/fv48+vfz7+///8ABijggAQWaOCBCCao4IIMNujggxBGKOGEFFZo4YUYZqjhhhx26OGHIIYo4ogklmjiiSimqOKKLLbo4ou2JaBAAjA2pAABChSEAI0uJoBAQQQESZAAQraYQJACEBQkAQMdieOLS/IIwJID3UjAjy4iEGSOAlEJgJZPwmglllQ6SYCUAqF5opk0UglmkgOBqaaHRyqApUBEXmnQkTzKuOSdIIKJY596JpRAnkiWiCgBAsx50JKDrmllkQuBCeiJljq0o5GX1qgRpFs6mqGfoEIE6pYgTgqpqaDOCCKpq3r/2tGmLCJwgKZBdlriAAwwMICNS7pqIgEL9NprQ4dCCueIBhjLgAHLHiTAAH1OqiuHvPa6QAECIbCtQQQMMAC3cd4o6oYF9PrrQAcssMCvBsQLQALiDnDtiGoS6y6N8RogkAL11miAu+v2O1AB4nLZ4gDu+iuQwd0G7OLACzD5sLwHi3tuie7eOhDEVd477LrsGuCxrAgRYAC5KLfs8sswxyzzzDTXbPPNOOes88489+zzz0AHLfTQRBdt9NFIJ6300kw37fTTUEct9dRUV2311VhnrfXWXHft9ddghy322GSXbfbZaKet9tpst+3223DHLffcdNdt991456333nz3OO3334AHLvjghBdu+OGIJ6744ow37vjjkEcu+eSUV2755ZhnrvnmnHfu+eeghy766KSXbvrpmgcEACH5BAkKAAAALAAAAABAAUABAAj/AAEIHEiwoMGDCBMqXMiwocOHECNKnEixosWLGDNq3Mixo8ePIEOKHEmypMmTKFOqXMmypcuXMGPKnEmzps2bOHPq3Mmzp8+fQIMKHUq0qNGjSJMqXcq0qdOnUKNKnUq1qtWrWLNq3cq1q9evYMOKHUu2rNmzaNOqXcu2rdu3cOPKnUu3rt27ePPq3cu3r9+/gAMLHky4sOHDiBMrXsy4sePHkCNLnky5suXLmDNr3sy5s+fPoEOLHk26tOnTqFOrXs26tevXsGPLnk27tu3buHPr3s27t+/fwIMLH068uPHjyJMrX868ufPn0KNLn069uvXr2LNr3869u/fv4MOL/x9Pvrz58+jTq1/Pvr379/Djy59Pv779+/jz69/Pv7///wAGKOCABBZo4IEIJqjgggw26OCDEEYo4YQUVmjhhRhmqOGGHHbo4YcghijiiCSWaOKJKKao4oostujii7YloEACMDakAAEKFIQAjS4mgEBBBARJkABCtphAkAIQFCQBAx2J44tL8gjAkgPdSMCPLiIQZI4CUQmAlk/CaCWWVDpJgJQCoXmimTRSCWaSA4GppodHKoClQEReadCRPMq45J0ggoljn3omlECeSJaIKAECzHnQkoOuaWWRC4EJ6ImWOrSjkZfWqBGkWzqaYQELMGDqqRCBuiWIp7bKQKqgzv8IIqmuvuppR5uymMAAmgbZaYkDLLBAATYuKauJBBggrLANHQopnCMesOwCB0B7kJZ9Tvorh8EKawCTX35r0JsEIXCjqBsSICyvAx1ggAG8DiAvAGyuqGay79IoL7tgcvmiuwYQC8C+Vfr6YgHvHjAQwWl62eK74grEMJ5BoltiwgRNLFCuLRIg8EAFDPDxrQcJMIC1JKes8sost+zyyzDHLPPMNNds880456zzzjz37PPPQAct9NBEF2300UgnrfTSTDft9NNQRy311FRXbfXVWGet9dZcd+3112CHLfbYZJdt9tlop6322my37fbbcMct99x012333XjnrffefPcz7fffgAcu+OCEF2744YgnrvjijDfu+OOQRy755JRXbvnlmGeu+eacd+7556CHLvrolAcEACH5BAkKAAAALAAAAABAAUABAAj/AAEIHEiwoMGDCBMqXMiwocOHECNKnEixosWLGDNq3Mixo8ePIEOKHEmypMmTKFOqXMmypcuXMGPKnEmzps2bOHPq3Mmzp8+fQIMKHUq0qNGjSJMqXcq0qdOnUKNKnUq1qtWrWLNq3cq1q9evYMOKHUu2rNmzaNOqXcu2rdu3cOPKnUu3rt27ePPq3cu3r9+/gAMLHky4sOHDiBMrXsy4sePHkCNLnky5suXLmDNr3sy5s+fPoEOLHk26tOnTqFOrXs26tevXsGPLnk27tu3buHPr3s27t+/fwIMLH068uPHjyJMrX868ufPn0KNLn069uvXr2LNr3869u/fv4MOL/x9Pvrz58+jTq1/Pvr379/Djy59Pv779+/jz69/Pv7///wAGKOCABBZo4IEIJqjgggw26OCDEEYo4YQUVmjhhRhmqOGGHHbo4YcghijiiCSWaOKJKKao4oostujii7YloEACMDakAAEKFIQAjS4mgEBBBARJkABCtphAkAIQFCQBAx2J44tL8gjAkgPdSMCPLiIQZI4CUQmAlk/CaCWWVDpJgJQCoXmimTRSCWaSA4GppocEMMDAAEMGiSVBR/Io45J7gjiAnQwsUECaVyqUAJFLwjmiAYQyYICjCi2J45whFrBApA2BGeiJg97p0I4tIoBnjR5ZuiWmGWoaqZ0Qqf+6JYivEhqrqjOC6OqrqHpEKosJnMqQpysWYIABhzJk5aUnKnDAscc2tKillIb4LLQHfKrjmWkuq22Hxh57AJMABFvtl0gShMCNrG5IwLHJClTAAAMwWWaUK6ppKr1tFgkmly/SOwCXXgIw5osKCDxQwWYGTO+eBQPAaLsl0ktul0XGSXGJWhZ0I8C9HiTjxiGXbPLJKKes8sost+zyyzDHLPPMNNds880456zzzjz37PPPQAct9NBEF2300UgnrfTSTDft9NNQRy311FRXbfXVWGet9dZcd+3112CHLfbYZJdt9tlop6322my37fbbcMct99x012333XjnrffefPcu7fffgAcu+OCEF2744YgnrvjijDfu+OOQRy755JRXbvnlmGeu+eacd+7554kHBAAh+QQJCgAAACwAAAAAQAFAAQAI/wABCBxIsKDBgwgTKlzIsKHDhxAjSpxIsaLFixgzatzIsaPHjyBDihxJsqTJkyhTqlzJsqXLlzBjypxJs6bNmzhz6tzJs6fPn0CDCh1KtKjRo0iTKl3KtKnTp1CjSp1KtarVq1izat3KtavXr2DDih1LtqzZs2jTql3Ltq3bt3Djyp1Lt67du3jz6t3Lt6/fv4ADCx5MuLDhw4gTK17MuLHjx5AjS55MubLly5gza97MubPnz6BDix5NurTp06hTq17NurXr17Bjy55Nu7bt27hz697Nu7fv38CDCx9OvLjx48iTK1/OvLnz59CjS59Ovbr169iza9/Ovbv37+DDi/8fT768+fPo06tfz769+/fw48ufT7++/fv48+vfz7+///8ABijggAQWaOCBCCao4IIMNujggxBGKOGEFFZo4YUYZqjhhhx26OGHIIYo4ogklmjiiSimqOKKLLbo4ou2JaBAAjA2pAABChSEAI0uFjBAQQQESZAAQraYAAMMGEBQkAQMlECQObqIJANNCsTkQDcSgMCLAyC5wEBXAoAAlDUugOSPAFz5ZJA8OrliAVNueeWYBAhAEJ1tgkjAAgagKZABSB5g0JM8ysjkliIOsMCiBlQpAAN+HpQAkUzaSeIBiy56AKILMYljniMSYECmXzJEJ6coKrpAAQ7taGSkNW7/5CmUoG5IwAEG5KorRLOS+aGuwCr5UK8z6olrsLF65CqLT7YaJKonKjDAAJYulOWnJyIw7bYNTepptSL6uG0Btd5JQKHXQuuhtNMWYCmhBtEJLgI3lsuhtgNEKRClcgq55rkrgvovjWHSqa+LWSIaJgAJv2gwmEUC8O+LWba5MACU2mtikOBeLKbGJiYA7Y0HJztosSanrPLKLLfs8sswxyzzzDTXbPPNOOes88489+zzz0AHLfTQRBdt9NFIJ6300kw37fTTUEct9dRUV2311VhnrfXWXHft9ddghy322GSXbfbZaKet9tpst+3223DHLffcdNdt991456333nz3M+3334AHLvjghBdu+OGIJ6744ow37vjjkEcu+eSUV2755ZhnrvnmnHfu+eeghy766JcHBAA7";
        loadJsImg.width = 320;
        loadJsImg.height = 320;
        var canvasNode = document.getElementById(c.tag);
        canvasNode.style.backgroundColor = "white";
        canvasNode.parentNode.appendChild(loadJsImg);
        
        var canvasStyle = getComputedStyle?getComputedStyle(canvasNode):canvasNode.currentStyle;
        loadJsImg.style.left = canvasNode.offsetLeft + (parseFloat(canvasStyle.width) - loadJsImg.width)/2 + "px";
        loadJsImg.style.top = canvasNode.offsetTop + (parseFloat(canvasStyle.height) - loadJsImg.height)/2 + "px";
        loadJsImg.style.position = "absolute";
    }
    
    var updateLoading = function(p){
        if(p>=1) {
            loadJsImg.parentNode.removeChild(loadJsImg);
        }
    };

    var loaded = 0;
    var que = engine.concat(c.appFiles);
    que.push('main.js');

    if (navigator.userAgent.indexOf("Trident/5") > -1) {
        //ie9
        var i = -1;
        var loadNext = function () {
            i++;
            if (i < que.length) {
                var f = d.createElement('script');
                f.src = que[i];
                f.addEventListener('load',function(){
                    loadNext();
                    updateLoading(loaded / que.length);
                    this.removeEventListener('load', arguments.callee, false);
                },false);
                d.body.appendChild(f);
            }
            updateLoading(i / (que.length - 1));
        };
        loadNext();
    }
    else {
        que.forEach(function (f, i) {
            var s = d.createElement('script');
            s.async = false;
            s.src = f;
            s.addEventListener('load',function(){
                loaded++;
                updateLoading(loaded / que.length);
                this.removeEventListener('load', arguments.callee, false);
            },false);
            d.body.appendChild(s);
        });
    }
})();

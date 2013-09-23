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

/**
 * resource type
 * @constant
 * @type Object
 */
cc.RESOURCE_TYPE = {
    "IMAGE": ["png", "jpg", "bmp","jpeg","gif"],
    "SOUND": ["mp3", "ogg", "wav", "mp4", "m4a"],
    "XML": ["plist", "xml", "fnt", "tmx", "tsx"],
    "BINARY": ["ccbi"],
    "FONT": "FONT",
    "TEXT":["txt", "vsh", "fsh","json"],
    "UNKNOW": []
};

/**
 * A class to pre-load resources before engine start game main loop.
 * @class
 * @extends cc.Scene
 */
cc.Loader = cc.Class.extend(/** @lends cc.Loader# */{
    _curNumber: 0,
    _totalNumber: 0,
    _loadedNumber: 0,
    _resouces: null,
    _animationInterval: 1 / 60,
    _interval: null,
    _isAsync: false,

    /**
     * Constructor
     */
    ctor: function () {
        this._resouces = [];
    },

    /**
     * init with resources
     * @param {Array} resources
     * @param {Function|String} selector
     * @param {Object} target
     */
    initWithResources: function (resources, selector, target) {
        cc.Assert(resources != null, "resources should not null");

        if (selector) {
            this._selector = selector;
            this._target = target;
        }

        if ((resources != this._resouces) || (this._curNumber == 0)) {
            this._curNumber = 0;
            this._loadedNumber = 0;
            if (resources[0] instanceof Array) {
                for (var i = 0; i < resources.length; i++) {
                    var each = resources[i];
                    this._resouces = this._resouces.concat(each);
                }
            } else
                this._resouces = resources;
            this._totalNumber = this._resouces.length;
        }

        //load resources
        this._schedulePreload();
    },

    setAsync: function (isAsync) {
        this._isAsync = isAsync;
    },

    /**
     * Callback when a resource file load failed.
     * @example
     * //example
     * cc.Loader.getInstance().onResLoaded();
     */
    onResLoadingErr: function (name) {
        cc.log("cocos2d:Failed loading resource: " + name);
    },

    /**
     * Callback when a resource file loaded.
     * @example
     * //example
     * cc.Loader.getInstance().onResLoaded();
     */
    onResLoaded: function () {
        this._loadedNumber++;
    },

    /**
     * Get loading percentage
     * @return {Number}
     * @example
     * //example
     * cc.log(cc.Loader.getInstance().getPercentage() + "%");
     */
    getPercentage: function () {
        var percent = 0;
        if (this._totalNumber == 0) {
            percent = 100;
        } else {
            percent = (0 | (this._loadedNumber / this._totalNumber * 100));
        }
        return percent;
    },

    /**
     * release resources from a list
     * @param resources
     */
    releaseResources: function (resources) {
        if (resources && resources.length > 0) {
            var sharedTextureCache = cc.TextureCache.getInstance();
            var sharedEngine = cc.AudioEngine.getInstance();
            var sharedParser = cc.SAXParser.getInstance();
            var sharedFileUtils = cc.FileUtils.getInstance();

            var resInfo;
            for (var i = 0; i < resources.length; i++) {
                resInfo = resources[i];
                var type = this._getResType(resInfo);
                switch (type) {
                    case "IMAGE":
                        sharedTextureCache.removeTextureForKey(resInfo.src);
                        break;
                    case "SOUND":
                        sharedEngine.unloadEffect(resInfo.src);
                        break;
                    case "XML":
                        sharedParser.unloadPlist(resInfo.src);
                        break;
                    case "BINARY":
                        sharedFileUtils.unloadBinaryFileData(resInfo.src);
                        break;
                    case "TEXT":
                        sharedFileUtils.unloadTextFileData(resInfo.src);
                        break;
                    case "FONT":
                        this._unregisterFaceFont(resInfo);
                        break;
                    default:
                        throw "cocos2d:unknown filename extension: " + type;
                        break;
                }
            }
        }
    },

    _preload: function () {
        this._updatePercent();
        if (this._isAsync) {
            var frameRate = cc.Director.getInstance()._frameRate;
            if (frameRate != null && frameRate < 20) {
                cc.log("cocos2d: frame rate less than 20 fps, skip frame.");
                return;
            }
        }

        if (this._curNumber < this._totalNumber) {
            this._loadOneResource();
            this._curNumber++;
        }
    },

    _loadOneResource: function () {
        var sharedTextureCache = cc.TextureCache.getInstance();
        var sharedEngine = cc.AudioEngine.getInstance();
        var sharedParser = cc.SAXParser.getInstance();
        var sharedFileUtils = cc.FileUtils.getInstance();

        var resInfo = this._resouces[this._curNumber];
        var type = this._getResType(resInfo);
        switch (type) {
            case "IMAGE":
                sharedTextureCache.addImage(resInfo.src);
                break;
            case "SOUND":
                sharedEngine.preloadSound(resInfo.src);
                break;
            case "XML":
                sharedParser.preloadPlist(resInfo.src);
                break;
            case "BINARY":
                sharedFileUtils.preloadBinaryFileData(resInfo.src);
                break;
            case "TEXT" :
                sharedFileUtils.preloadTextFileData(resInfo.src);
                break;
            case "FONT":
                this._registerFaceFont(resInfo);
                break;
            default:
                throw "cocos2d:unknown filename extension: " + type;
                break;
        }
    },

    _schedulePreload: function () {
        var _self = this;
        this._interval = setInterval(function () {
            _self._preload();
        }, this._animationInterval * 1000);
    },

    _unschedulePreload: function () {
        clearInterval(this._interval);
    },

    _getResType: function (resInfo) {
        var isFont = resInfo.fontName;
        if (isFont != null) {
            return cc.RESOURCE_TYPE["FONT"];
        } else {
            var src = resInfo.src;
            var ext = src.substring(src.lastIndexOf(".") + 1, src.length);

            var index = ext.indexOf("?");
            if(index > 0) ext = ext.substring(0, index);

            for (var resType in cc.RESOURCE_TYPE) {
                if (cc.RESOURCE_TYPE[resType].indexOf(ext) != -1) {
                    return resType;
                }
            }
            return ext;
        }
    },

    _updatePercent: function () {
        var percent = this.getPercentage();

        if (percent >= 100) {
            this._unschedulePreload();
            this._complete();
        }
    },

    _complete: function () {
        if (this._target && (typeof(this._selector) == "string")) {
            this._target[this._selector](this);
        } else if (this._target && (typeof(this._selector) == "function")) {
            this._selector.call(this._target, this);
        } else {
            this._selector(this);
        }

        this._curNumber = 0;
        this._loadedNumber = 0;
        this._totalNumber = 0;
    },

    _registerFaceFont: function (fontRes) {
        var srcArr = fontRes.src;
        var fileUtils = cc.FileUtils.getInstance();
        if (srcArr && srcArr.length > 0) {
            var fontStyle = document.createElement("style");
            fontStyle.type = "text/css";
            document.body.appendChild(fontStyle);

            var fontStr = "@font-face { font-family:" + fontRes.fontName + "; src:";
            for (var i = 0; i < srcArr.length; i++) {
                fontStr += "url('" + fileUtils.fullPathForFilename(encodeURI(srcArr[i].src)) + "') format('" + srcArr[i].type + "')";
                fontStr += (i == (srcArr.length - 1)) ? ";" : ",";
            }
            fontStyle.textContent += fontStr + "};";

            //preload
            //<div style="font-family: PressStart;">.</div>
            var preloadDiv = document.createElement("div");
            preloadDiv.style.fontFamily = fontRes.fontName;
            preloadDiv.innerHTML = ".";
            preloadDiv.style.position = "absolute";
            preloadDiv.style.left = "-100px";
            preloadDiv.style.top = "-100px";
            document.body.appendChild(preloadDiv);
        }
        cc.Loader.getInstance().onResLoaded();
    },

    _unregisterFaceFont: function (fontRes) {
        //todo remove style
    }
});

/**
 * Preload resources in the background
 * @param {Array} resources
 * @param {Function|String} selector
 * @param {Object} target
 * @return {cc.Loader}
 * @example
 * //example
 * var g_mainmenu = [
 *    {src:"res/hello.png"},
 *    {src:"res/hello.plist"},
 *
 *    {src:"res/logo.png"},
 *    {src:"res/btn.png"},
 *
 *    {src:"res/boom.mp3"},
 * ]
 *
 * var g_level = [
 *    {src:"res/level01.png"},
 *    {src:"res/level02.png"},
 *    {src:"res/level03.png"}
 * ]
 *
 * //load a list of resources
 * cc.Loader.preload(g_mainmenu, this.startGame, this);
 *
 * //load multi lists of resources
 * cc.Loader.preload([g_mainmenu,g_level], this.startGame, this);
 */
cc.Loader.preload = function (resources, selector, target) {
    if (!this._instance) {
        this._instance = new cc.Loader();
    }
    this._instance.initWithResources(resources, selector, target);
    return this._instance;
};

/**
 * Preload resources async
 * @param {Array} resources
 * @param {Function|String} selector
 * @param {Object} target
 * @return {cc.Loader}
 */
cc.Loader.preloadAsync = function (resources, selector, target) {
    if (!this._instance) {
        this._instance = new cc.Loader();
    }
    this._instance.setAsync(true);
    this._instance.initWithResources(resources, selector, target);
    return this._instance;
};

/**
 * Release the resources from a list
 * @param {Array} resources
 */
cc.Loader.purgeCachedData = function (resources) {
    if (this._instance) {
        this._instance.releaseResources(resources);
    }
};

/**
 * Returns a shared instance of the loader
 * @function
 * @return {cc.Loader}
 */
cc.Loader.getInstance = function () {
    if (!this._instance) {
        this._instance = new cc.Loader();
    }
    return this._instance;
};

cc.Loader._instance = null;


/**
 * Used to display the loading screen
 * @class
 * @extends cc.Scene
 */
cc.LoaderScene = cc.Scene.extend(/** @lends cc.LoaderScene# */{
    _logo: null,
    _logoTexture: null,
    _texture2d: null,
    _bgLayer: null,
    _label: null,
    _winSize:null,

    /**
     * Constructor
     */
    ctor: function () {
        cc.Scene.prototype.ctor.call(this);
        this._winSize = cc.Director.getInstance().getWinSize();
    },
    init:function(){
        cc.Scene.prototype.init.call(this);

        //logo
        var logoHeight = 200;
        var centerPos = cc.p(this._winSize.width / 2, this._winSize.height / 2);

        this._logoTexture = new Image();
        var _this = this;
        this._logoTexture.addEventListener("load", function () {
            _this._initStage(centerPos);
            this.removeEventListener('load', arguments.callee, false);
        });
        this._logoTexture.src = "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAgQAAADACAYAAAB75HsdAAAACXBIWXMAAAsTAAALEwEAmpwYAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAYnRJREFUeNrsXQd4FFUXvRAEQkkChN4WgiChJBSVIrB0UBFQQBTFBbGALdixYFDsCrELUoJ0QQg/oChtQ0daQpe6tNDTKEmQ8s8b5i1vZ2d2p7zZFO75viHLlunz7nm3nFvoxo0bUNBQqFChaOGPXVgcwhImLL2E40wS3ievo4XXTkAgEAgEAuFG4QJEAmzCEl+4cOFM4b/bgoKCvixVsmRD4XVNYVlFPhP+HpGIAgKBQCAQCNaO5ncPAZn1lygRPOby5axBpUuXui78v3D1alUhNLS0+PnBQy44ffosCOTg2vUb168I39snHHM0XnoEAoFAIAoIISChAcHQLylTJrRik6iGAgkIg+07d10rWbJEEPu98+fToFy5MnD8xEk4evQ4SJ4CB4YOEAgEAoG4CcMhA8EYxxA3vLA4cmPHq1Su2KZEieC1997TtKK97X0iGUg5eRJKBAcHyb9LyABBxfLhUKRIEbLvRXmSARquEBanlL+AQCAQCETBJwSC0YsV/owVlqeEZbJkCMMC6BkIy8i8sKR7lw4lqlSu7H7/2PETVwoVLqT6u5wrVyAoKOigQAYiOe5LL+FPknQu2glLLN5WCAQCgbgtCEHRone8Tv6Gh5elb7UTZuvryEw5EDtdrmyZnYQMlChR0v3e2XNnQXijqNpvrl29JhCGlI3Z2dl1BEKQzokMxAh/5nfq0Lb4c0MGCdsPzgFMWkQgEAhEPkQRgzNi0RKfO5cKn34yGjauXwMJC5fUL1Wy5N5q1aqMOn485VOrdrhG9aqz7m4eXZUlAze9AyevhYaW9goXZGVlQ3BwcThz9ty+tLT0brw8FI0bRf51f9cOjStVqnz1yaeGFKtWvRqULFW62Ji4b4vhbYVAIBCIAu8haBLdqBuZDbe4p5n4/xHvvAfFiwfDqzEvw8VLl4qdOHHyk/ByZc9JOQZcPQYkb6BcubK9yoeX95z9X7sGOTk5XrGCixcvweXLWSIpSM/I/MCsZ4DkB7RqcffciNq2kyNHjrrnzbdHFi9cuPA1QgbEc9O0Od5RCAQCgbg9CIFgeG3CTBh++HE89On9oPjerDnzYcqvU28M6N8H2rVpCedT08rBzRyDw4IRTZLIgelku0KFCk+PvKue1wz89JkzUCYs1OtYjh47DmGhISS3YE9qatosI54A4hEJCSk9g5Ac4a1tjRo2fGTd+o3FCQl57dWXYegLMe79iYxsgHcUAoFAIPIldIcMjh1PCbt08QKECIb20y/GQodO3WDMmK/hwMHDhabPmkvi+9D2vhZQvVo1WLrcSVz1URI5IAaWlPslCEs8UQ7Us93atWr2r3/XndWDgryiAnDk6HEoH17OyzsQVDiI7C9cunh5vh4SIPzpJS09yXvVq1W5fl+rVoXfHPEeFC5cGObP+x2+/PIL+PrrseJ5oCCvK5QPz8DbCoFAIBAFnhBcuHBxievI4Xvp/zt36Sou8ZMnwowZM64fdh0tvGrNBihTJgwe6dUDWrZuC7t27oCly5bCjp17iGrgK2SRyEG8RA5cGjY9mq0ouH79umicCdLS0q9XqBDu9hD8d+U/0Ttw8eJlCAq6nJGdnf2uBiLgYElAy3ubX+nb71Fo27Y9NGverHBmZibs2L4D/rdgHvw+b55IBho0bOixjuPCNitWLJ+OtxUCgUAg8ht0CxORksOQkNLvbdmyNUjp83m/z4G5c367vmlLkttA39+1AwweMhSimzQRDOp8WJAwDxJXr2d/NkVYYtWIQYPIeveHlC69+M46EeL/yT5nZ2dBcHAJyMhIh737DkC45CEgZGBb8k64evWq+P/g4sUnX87KGuzDGxATFBQ0+Nq1a9X79H4wo/sDPUN79X4Yypa9WUFB1rN7125IStoKc2ZPh1Onz954f+SoQpENvMMDG9avhx++/2bt+o2b78NbC4FAIBD5CUbKDpMyMy8E7d61S/HDhx/pCzNmzSm8ICEBnny8n/jeH3+tgD59+8L93buIRty5ah0cOHBATESMrF/3Otys4T8sift46RlcvHT5q9q1bO7/X7mSIyxXxNdHj6dAenqm+7P9Bw+5yYBg6K/6IAO9SpQI3l29WpXX3nt3RHWyP3PmLQwd/PQQkQyQdezbtw8WLVwI333zNcQMHw6VK1eFceMnKZIBiqAiQQfwtkIgEAjE7UAInOSfTZs2+vwSMZojR30MWzZvAcHgQkRt2/V9+w/B0GEvQAf7ffDPxo3w0cefwq7d/xaeOOEXaNSwPvnZU8KMPkUqbXTP4oMKF65JcgcICSDJfP/995/42aVLF+H4iRSSpyB6Bog0MUsOihUruk/JK1CvbsQaYX9mfvftt5WPHjtRKnbURxAREeH+zrFjx2DN6jUw8Zdx8OqrMXDYdfj6vN/nA8khYHMG5Ni2dTMpxVyKtxUCgUAg8hsM9TK44447djRvGtVw6nR9ifsknDBx4oQbAjEQSwT79O4BQ559AarXqC7Oyn/+6QcY9eFo8bv33t103IZ/tjxfo3rVkXXvjBhF8geysi67PQMUxPtAZvOlSpYkZY8en4WElL4vIyNzLf1/187t26Smpv3xwIM9Sr38ynB3WIDi/PnzYp7Apk0bYMaM6SRf4sarr75WqEtXbfIFI9996+LM3+Y10pgTgUAgEAhE/iYEkkLfWBIWYN3nJIa+9K/FEF6+IlSsVAnuuacl0Bp9FlPiJ8FPP/1MyhMhLCwEXnn5ZWjRorXYZ4DszxNPPC7O+uveWXthalp6rS4d2zekHgF2fwkRWJm47kZWdraXBkGxYsUuZGdnh7BkwHXk6LIZM34r2qx5My8icGD/ATh27CgsmD8Hps2cA0MGDbw69IVXirAeAXJ8xAtAMfSFlzzWM+z5Iaf+XuasjLcVAoFAIPIbihj8HSkdHPv7nJkCIRjtfvP77+Jg46atHl+sV7cO2Nu2gf6PD3STg6ccg6F37z7wzdgv4Nfps0WvwAPdOoJj8HNQqlRp+O6772H06FGkKqFHeHjZnOvXr8Hly5e9duLipctw/cYNxeYFQUGF99DXA/r3aUycCes3bCrKegXIOvfs3gNnz56FHTuSBJLyE6lcuDH1118LtWjZUjw3S//+C1Ys+wvmzl/osf6VK1Z6/D8zI5NUO5zDWwqBQCAQt42HQPISEB2BKJIjQGfRZMa+bOnf4kx+7+5dsHrtOjh4yOX+zcABj8Kgp5/38BoQg/v++++L3oLoqIbwzDPPQe3adcR1DBs2VPQU3Ht3U6hYIdxrH86eS4Wk5J2QlZ0tIwNBRA/hgdNnzv5Bcgb69+21/YefJ1aXVw6kpKSI/yfEZsLkX+GZwU/B88NeFo+HhDcmTZoE/+47AM2bRkHDBg3grsgGUKlSZYiMbAhlypbx2KZUXfHGP5u3fYW3FQKBQCBuJ0LgEP5MJpUCrOs8TTDsbJz/wIF9sOSP/8GsOQnu9+S/IbPrF4Y9Cxv+2SKGED4e/bFICohh79K1C2mmBO3atILg4p4ihQcPH4Vdu/d67Zvw/Ss5OVeKSd6BJa++PqIrCRMQInDo0CE4euSo9PoATJgwHjIzL1yPjf2wcIuWLYFUT3zy8Yew78Ah6Png/fBAj15QuXIVj/UTMlC0qGcfpSGDB15MXL0e8wcQCAQCcXsRAokUEONXk7jP6ayfVAGcP3ce5Os9eTJFmInPcBMD0gvh08++8vAWfBT7nhhCoKSgbt27xAS/d959H6pWrQzNohuJ3zuRcgpOnTkrzPBPgdL+lygRfPDSpct1+j3Ss3/L1m1mDn/1dbFy4OCBg5AteRP+WJQA02bOhg7tWsM7733o9gq89fY74HjycTHEUapUKYV1l4DSIaU93iOCRAMHDkg5euxEVbylEAgEAnE7EgJSHji/a2c7fP/jL+73yew79XyqorHetm0LxMWNFUMJROZ40qTJHomJLCn4Ju4baNGyFfR/tA9sS9oBlStVEEMLV678R7adI6z/TNGidxytUb1a9IGDh93tD4sVK7YqJyen5zODn9r56RdfV927Zy9cuHBB/OzMmVMwaeJ42L5zj0A6RosqiwSjRr4De//dBy++9ArUqVNX8XhJ0mM5mUQy3ec9e//FcAECgUAgbk9CIJECp/CnnTwM4IsUXLx4EX76YSwsWPSXT1JAcgq+/HIsZGZmwCN9+oifCQRgT+OGkdnh4WXDBWJQOjSk9NWatohLWZcvFU5NPV990R9/i1UHwnrT33lnRFhkZCP3epW8AgSx74+Aa9euwosvv656nIQMlC1Xlhyvl3egR48Hr1y8dKmi2W6KCAQCgUDkZ0JAlAVdwhL6+WefiEqFFCR8QPID5NoBFN9/+5UYQlAiBU8O6C/mFAwZNBCOHD0CS5cnat4nkntAtt2xfRt4/Y13xAqCmTNnkFyBG6+99noh6hUg+PyTjyA0LAx6P9xPNxkgGPHmq7Atecc3Bw4ejsHbCYFAIBC3LSGQSEG0sCQK6wqRkwLRI3DhIlySiQbJSQHJKSAtlemsncy8+/R5WAwRlCgRfCOitu1ATMyrd9asWcvj99u3b4OMjAw4sG8vJG3f6ZVkSFQRVzjXeFQQUMydMxvOnT3jkwwEBweLOQNKZIBUSLz+xhs5ly9nVULvAAKBQCBue0IgkQIxn4C8fm7IIHj9rXc8PvflLXj/vbdgZeJar9/NmD4VPoj9kCgOnsjIyCQZfqH+9sO50glO53JYt3a16FUoVqwY/DZ7Nsj7Dxw7egymTpkATz8zTO14xKTCEiVLKH5OjqVjp/bXgwoHfXnufOrbeCshEAgEIj+jCK8VCcQiQTCi7YWXCeMmTA51HTkMb4/4wF1FQNz4pFyPEIJLFy95EIO33n5fmN33F4yvZ1Z/8eLFSc7Af08+/th1gSyEkoTAhIVLPL7Trk1LKBMWClFNmkOjRlFwV/36ouohWUiL5OUrV8Pevbu9CMH0qZPh0ccGKp+UIkUgVFgn+atGBoY+P+Ta9es3DqalIRlAIBAIBHoIlGbW0cKfeGGJKlMm7MYLw4YWIsqEcsiJAWkv3KJFK9EQUwwZPBBWrdlwVdhHXcSFqB42aBglLI3g+eeH3mjbpkUhtgqC4NzZc6LXQo9XgJIBopmwLXlnVk5OTiTqDiAQCAQCCYE6KSCJhrHC8gr5P5EvHjx4sFduASUG2VnZRDIYSpX29BC0bdP66slTZwx7MUjpYmnBwB87ngKsoiLBhcwLHnLIvnIFVMhAK+HcJeEthEAgEAgkBNq8BXHC0o4Sgwfuvx/a2Tu4XfikYZAckZEN4PjxY9C/f///srKz7yDvsaEBNSRv2wzrNmwW5Y7lkCc7krJIIqBEFAcJEVALD1CQ/Rw16oPrwrrPZ2Ze6IJkAIFAIBBICIwRgxjB6PYRDLEoIBRcvLhXDwI5ihUr9l/PB7ve8dgAh1s+mBhvm80mKgaqIfaD92HXjmSPhkTCeuCrsd97fI+QAn9EgHgFxv/8PYybMBnKlAlbmpaW3g8rChAIBAKBhMAYISAhBFKn7xCWmiVKBGf3fLD7GXuHzuUjIu4MbtK0CdDGQ8uXLRf/Llmy6PTe3TuvLfpzmcgEiEhRl85doH2HzuLnNWrWgLp16yoa9CV/3kw8JL0KfvllnNgAqXq1KrBipXYtA1L2uPB/82FSfPz1LBIgyMkZJpyreLxlEAgEAoGEwBgZICSAhA1C+/ftdWzIsy9W79ipo651jB/3c9bsWdOvrXCuKVXLVgOGDh0KjRpFi1UITZs1hZCQEI9Z/7Klyzx+/8orL8C+/Ydg//79fr0By5b9BZs2rhe9C8WKFSNU4Auy/+gVQCAQCAQSAmNEwAY3qw3a9X6o+7kvx3wXHhERYWqdxHsw+qORF5yr1pXu07sHPPrYkxAWVgbuufceNyk4f/48bPpnk8fvJv7yo2jg2SZMlADs3r0Ltm3dDOvWrRWVEQlCQkrvy8y88KnwMgGJAAKBQCCQEBgnA0SkKJ40I5o6dUaoXo+AP3z26cfZI955rzhZf8f27aBEiZIQXr4C3FG0qJhrUK5cOJQqVZohEkvgqzHfiDLIIaFhsGvXdnAdOQ7/7jvg/o5EAn6SSIALbw0EAoFAICEwRwZIrsBY4hWYMHlaOM0N4A1SRtiiZYsbV69eVawTJDkHbVq3hrb2jnDmzGl44cVbjZeCixfPDgsL+ffkqTOkFzOpFnCiJwCBQCAQSAj4kYF44c9TAwc8mjpl2qyyVu88IQVt27W5lpWVHdSyRXMoVbKk2FaZLCyIUNHiJWKy4hRhiUHjj0AgEAiERYRAIAOxwp8Pxv38U9azzz0fHKgDIKTAbm93rU6dWkFjxnwLOTk5YnXB+rWrYNGff0F6eib79VHC8cbiZUcgEAgEwgJCIFUSTB767NPnfhw3ITzQB0GSDTt17iTmCDzS9zH3+xcvXoBN/2yAOXPnwmHXUfLW78Lx9sHLjkAgEAgEZ0IgiQ45Bw549FogwgRqeP6ZwefHTZhcbkr8ZKhQoZLX5889/wwcPXp8oXC8D0kVEDbm43RUHkQgEAjE7YzCHNYhVhOM/fbHsrl5IJ98/lW5kJDS1xYumOf1GemSWK5sGfKykUAGCAM6LCwrmWUbeV9YEiRvBwKBQCAQ6CHQ4R2IFf58sHnTZmjWvFmuH8yIt97I/OyLr0Kol2DHjiRIXLmMJhRCty7tj7Vt16HUPfe0LBMWFibu88GDB8F12AX//LM+bdq0qdd279lHQh5H4GbyYQLeIggEAoFAQuCbDBA5YtfQZ5/+LzfyBpSQmpoK5cqVE3MJ0tPTRDGiWrYaOW+/PeJ6n779grWUQJJ8hA8+eOf02nX/VBT+O0U4P+gxQCAQCAQSAl/egeDixd88fuJEsFVaA0bQvWuHlCV/rxT7H4x4+43MTz79IsTIer784rPsN98aUVx4mSwsdixVRCAQCERBhqEcAtqsyDFwwKW8RAYIej/cT0wWIP0MjJIBgjfefLs4KaEUXkbBzV4MCAQCgUAgIZCBSBOHvvbmiPC8dkDNmt3NTQOB6ClIpOApSYERgUAgEAgkBCwhiKxf95zZZkWWEAIpuZEkCfIiBUSGWXgZK5UrIhAIBAKBhEBCzyeeeDIorx5UhfLhaWdOn87ktT7SkyG4ePGihBTgLYNAIBAIJAQg5g/Yyd8uXbqX4bEDpOzvjdeHnx7+yktHxo/7OYvHOmvZalwuLIDXSSJ5Eq+88tIVuBk6QC8BAoFAIAocihj4jWgQeegOkDLBxo0bZV++nFWRvrd2tZNLY6TCQYVL8DxRb7z5duhnn39JXpL8CUwyRCAQCMTt7SEghCC4eHEuM/kvv/gsQyADpLQvVXor69fps8uShkVmsHHT1qpBhYN8JheSbXz6yeg0ojug1UtAhI2Elw68bRAIBAKBhEBAZP26Z3hsPDsri9b2l2X3Jz3dfMm/rVZtVQ/BsOeGnGt+d3N45933y5CmSPa2rc5pWWfvh/uRqoooDBsgEAgEAgkBR9SPbFCBegaEJUdYihHvQ5OmTQyvk874q1Wrrvg5yVn4afzEcGmbBKmJq9eHa8lf6NipM/U6ROOtg0AgEIjbnhBs2ba9Jo+Nk5I+0jJZeBlMyUBc3FgwI3a0adMGQiygbbt2ip+TvgUSglnvxJ7du/x6PUiZpRQuQUKAQCAQiNueEIhtgklCIA+QPggHDhwQlQUvZ2UFE5JgdF3//fcfJG/bUqzH/Z0hKEi5KtJWywaMV0I8FJm3wid4hUsQCAQCgSgQhGDZ0qXcdoLMvDt26mhqHVevXoWUlBSYNWc+tLqvnc9tMV4J0UPQqGH9VJ1ExI63DgKBQCBua0Jw48YNV4kSwSf/+nOROCPPC7h27RpkZWXBzBnTxP8/9vgTqh4C6pUgLZtffy3m9Nw5c2D7jt1l8VZAIBAIxO0MIzoEcPly1vgFCxePHJmSUqhSpUpQrFixXDsAQkoIGSCYOvVXGPzUE1CmTBkioOTzd0RHQVgqGtysC28dBAKBQNzWHgIJ8edT0wqN//lHyMnJEQjCZTDaRtkMsrOz3WTgxx++g9179sErw9+4yXSKFLFkm8I2KiAhQCAQCAQSArgZNqgTUWvh+AkTxKx9Er+/dOmS+DcQIOSDkJArV66I/09LS4Ovx4wRvQM0adCKcAYpaczKzia5Bk68dRAIBAJRkFDI6My+UKFCYaVLlzpjb9Pyjmkz57rfJ7H74OBg4NhKwAOEdBCvALvfzw15Cv5a5ry+bVtSYRIuoCD7cccdd3Db9iO9HsxY9OffF3NyrlTDWweBQCAQt72HQJqlp997d9MXF/6xFIa//IL7fZLgd/HiRXEGT17zAlkX8ULIwxPTpv4Ks+YkQFpaeuGM9AyP3xDiQEIaPAjIooULYd6CxaFXrvz3Fd42CAQCgUAPgQwPdu80a/GS5Y/+8P138MSTA70ZR+HCYjy/aNGiur0GZN+IQSahASVykeh0wkM9e0Kf3j1gy7ZkaFC/Lkyf9bviPpDER7If/pINyXZIuIH8pdtM2pYEDz/c68Z/V6/uz8jIrIe3DQKBQCCQECigzX0t1qxZu7H1Sy88D6M/+Vx9Y4IxJiEFShLI/8lCiQI1wMQgX79+3WdOAjHSvXr3hJo1qsGnn34JO3YkwZtvjRDzCMZ++4O6S0TYFt0PArIdcg7IQl4rbYeQgYzMC5eE/WlE8ifwtkEgEAgEEgI/noL+fXvDZ1+OBTaWzxtT4ifDO++8K75u3DgSigjGve6ddSE7OwumzZwjkIIBMHLUx6b2gSQqkiqKTz77AkJCSu/LzLzwqHCukvCWQSAQCAQSAj/o90jP4UtXOL8UZv9Bo2JHKYYQzGL0h7Hw5ddjRQ+DmgeBfFaxYnn46cefoZ3drmv9pGpi9qzpMG78LzdIaaXw1jfCEktyJvB2QSAQCAQSAq0rLFTI1iDyrmW7du+NID0FnnnuRd1GWQkkX+Dj0aNg46at8MRjfaFxdFMxtyAzIwOOHXXBnn/3QVLyTq/fVa5UAZ566imoU+dO6NS5i5fXgIQEjh49Ant274RVqxNhzdqN4vulS5eaeeHCxXcwRIBAIBAIJAQmcE/zJg+mpWdMOHDwcMXI+nXhyScHwv3392CbC2kmAmPHfAErE9dCnYha0L1rF7DVjoDy5StCZGQDUXGQ4NixY3DwwEHS7RD27d0Dm7duVSQIaihWrNjloKDCzsuXs+YI/01AjwACgUAgkBDw9RjYm0Q3GrMtaUcT8v/7Wt8LTaKbwF31G0D16jWgcVSUx6ydzNi3bt0MzhV/w8pV6yAz84LfbbRr0xLq1a0Hde+qD3Xq1IWSJUuJ4YQzZ07B0r/+gJm/zSNhhGs5OTmdwLMxkZNuFgkAAoFAIJAQBGJDhQqF1bLVeDwn58powTCHSfF5TSAGv0l0U6hXPxLuvPNm1d/q1U44sG8vLF3uhDNnz3l8v0L5cOjetRM0aBQFjRpFQ8K832DchMnkoyaYGIhAIBAIRC4SAokU2IQ/hxcvWgTVqlWHH74bC6dOpcCmLUlw8tQZ9/dCQkpDl452aNm6DfTt1x9OnzoNR464YMeOZPHzNm3sYuiBtDIm2LJ5C8yY/itMmz7DixyUKRMGXTu1F9siCxguHG8cXnYEAoFAIHKXEMTd3Sz6lSbRwqz9f4u8jHef3g9Cpy73Q5++/cTQwW+zpsH6jRthx849iutr1LA+dO7UGR4fMNCdS/D73Lkw7deJkLBwiXzbUL161blHjhzri5cdgbjNB75ChXrBzfBhtPSWE242LUtCLyICCUEAULJkidTLl7PKyI36oEGD4SnHYPH/U+InweTJk0QSQD5ree+9UKVadUhLPQ9ZUkMjonpI8gNYo9+rRzfo0fMRGPz0EPH/Bw8ehC8+HQ3jJ8a7v1O1auWU48dTquJlRyBuSxJgE/7ECItDWEL9fD2ZEgRKFrDiCIGEgO8DeYM14E8MfBoe6dMHUlNT4dtvxsJPP/0seg3IZ90f6AlbNm2EOfPEPgVe6ypXtgw80L0LhJevCEuXLXV7EQiJiIl51YMYvPPWa/Db7wugXt066Xv/3V8GLzsCcVsRgTDhDwkVPsVhdYkSUXBJRCGdt0dB2N9oyXthYzwY1ItBBsMEJCeIfE0ISLWB8GclUREc9uJwt4t/7Jiv4LPPPheJADHmL774MixeOB/+t/hv8fOoxg2gRrUqEBoaBpcvX4IjR4/DqTNn4cSJk+51P/u0A0qVDvHIISCJiO+P/Ag6duoIGzcIxOK3GeB0Oi9u3ppcGi87AnHbkAGHRAZCLd5UsmSsqdEmoQenTtJCvRc1NW4vTthGPF5lRL4lBHR7y5cth+HDX3LP7F+NeVmUHv7x518gPLwstLynGVSrXlMMD7DIyc6Gs2dPQ+aFi3Dg4GE47Drq/uylYc+Jn5HuhxQD+vcRxZH++Wc9/O9/CTmr12wojpcdgbgtyEA8J6+AUYwSxrtYjfsaKxECvcTlCCEResgHApFnCMH58+fh5Reeg+mz5orvkxLB119/DX6fO0c07m1a3ysSAV8gzY9OphwXmyFlZedA8vZdbs8A8TI88kgf+PHHn9zvES9EtWo14Pvvxl51rlp3R36+YA+MXktmEiQhKlpayP+jpIHBBbfingmL32vtwlscgWQgV9FbGGMTdOx3L+n51rvvg9BbgMh3hIAQAGqoyeuxY+PghReHwd3NmojywnKPgBpIgiEpWaQ4ejzFrUxI1jts2FBYuWIZJK5eD19+8Rk0bBgFH4x85/rGTVuD8jEZIAPFfB0/WSAscQIxwNkD4nYkBdEMcSZLu1zYjQxhscmFz6QQgU0t/0D6vJfkNYji7ZFAIHKbENiEP4fp/ykZePvtN6FjezuEhoXpXufJlBNimIHi4qXLsGbdRrhy5T/x/999+w3MnTML3h4xUvx/7AfvXt/wz5ag/HzBBFJAzqMDtMcaCcQGTQIxQDVGBJKEwJMEL0PNeDAIYSAeBELaFSXTdVZH6PJIIBC5QgikG/sGJQOzZ8+Bt996DZo2barZKyDHhcxMOHfujMd7RLJ43cbNkJ6eKf7/xx++h1q1bgoYxY39PGfJ3yvzVQ6BQACiBUOe5MNjEKNxUCNJSHYkBYgCbOypkSX3ehK7+JIml0iCTSIIdukvzyTEI8L2bcz2iGGfrPLdBRJBUCMHdDLQTo9HAoHIc4SgTJlQl2Coa27etBlGvP0aVK1S1ZBngEIeNlAiBUSpcPy48WKFwh+LFhybNWd+jXxEBugAd0QaJOKVyIHkNdAyg0BSgCioZMCXkQW4lWPjlEiCy1e5oOSyZz0JNpPeBLdsurDudI2EY4pEDBJ0eg0wdIDI+4SgZMkSi6OjGt7/0kvDhdn6V9CiRQtT68tIT4fU1HOKn7GkYMiggWLjo5MpKRPGxH37TD4hA2oDHDHqhCgoJg1Kv/MVd0wWfheNtz6iAJEBm2TkjczqqTfBTRb8eBNsEjkgnoQwhiz4C9+JsukaiIsamSGkIE5Jf0BaJ/vMZwjfC8M7A5GnCYFUWvNBpw5toVLFilAuvDwcOrgf/t1/8KYHISwMqlWtDBUqVvYbRrh+7RqkpBwXyw/PnjsvLv9d+Q/uKHoH1KhWFcqHl4X0jExYtWYD2GpWh04d2sP169dtE+OnHskHZCBMGqD8DXALJK9BgsI6oqVBQilbeZTwG5xBIAoKIYgHvhUFGeAZcnBpKeuTQg9hcKujKv1/mDTTjxW+Q57Vnib2LZFOCBQSFekzT0KJDswlQOR1QkBu2G3k9SO9HhDLC+fNT4Bjx73d/kRYKDKygSoxIGWHpCkSq0NAUa9uHah3Z23x9aq1G0QvQb9HHro6e+6CfFFyKBhzkTjpHMDIIBEn9xpI5EIueCLGGTF0gCgg3oHDAdrcEQWikKRzf7WGC7Q889RrkCTbhkhCUM0QoReFA7kx6cYVZ+g7dt0UJLqneRNlGrx6PSxa/IfYu0COUydTIGHhn4pkgKBG9VvtCipWqADBxYtD2bLhe/LRdYnR+X0ywLxCBkaBADilsIEIYvSJN0BYyMA5SJphhEqzCAQivyM2gNuqKc3uCVkn5b/bSKK0sDiJl4J4QEl5tWSQ1cCLhIdKXhGyD0kkbEC3SzwHSAYQeZ4QSCAzWdi3/5AYLiBegurVqih+kXgOtm7d6vFeWmoqLPzjL3dpoRwNIu8SCEAx9/8vXroElSpVgDbtOgzNJ94Bu8kZBEl8miysJ50kJUqhA0oOSHiBrL8J3vqIAoK8kA/TTjLOhCisJMMU8QRIRCFOMtY2yViTv7WEZbhEznmA5A5MlrYbL2m+IBC6EdCQgbjBmyyWxAiCyf8f7dMLypYLFw3/xk1bvb5f987a0L1bNzFn4OzZM2K1AO1zwKJo0TvgzjoREFHrVhEBSSz8e/kq6Nqp3eVFfy4rmY8IQQyYizPKIeqew81ERAwTIAreQHbTCNrgVsIf79JBs1BUEmQEiHpxfuYXCNtDLyAibxMC6SEgBm8seU3c+Y/2fVgsP7wszOZJ1QBJFCQoXqyoMLuvQr4P58+fFSWLb876L8PpM7eqC0JKl4IyYSFQpEgRj+3s2LUXzp1PhWLFii49dy71zfzU55yRKOY5UNC4YzyqFyJuA5JAqwBYstAul3anib/xhzM5SBS2h54CRN4lBOSGv+uuO2NPnDg59MKFix7ZgjTJkAXxCqSlpUJmZobubREykHLyNOTk5Hg8JGT2nZ+IgYwc6JEx9QeSy2HHfgeIfGrsiXF3gIHkPgUhIvK6poW7KwoTMftMyLi/8kazzzwSAkTeJQTkIaxcqYIzPLxcaEzMq9Ct+/3QvVtn2L5jt/s7bGUBUSFMSzsvNjDSAxImSNq+G86dPw/3tboXqlerBn/+tczdP0FCnhXukGL+LjXXviRCRAcKs4NY+4LmKZBCLgR0dgiSR+S2Jz4SsaTnhM6Y06Xzk69CSayXkYFcU8ClNblOwZsQzZF8Uw0Csu6VMlJO9lOULlYjCAyRcOh45pEQFBzyyxLYJCvLSQNCCHo+2HXk6nX/jPzqyy+DBj89xP3+hvUbYPSH78HiJcvd74WFhUDT6MZQqmQJ3UTgyLEU2PvvfvH/9epGwJgx30LXbl0hNTUVPv5oFIyJ+1Y+ePTKa9m4pEoAbro1E+lA4UO6mK07NhIvnSINnizI//N8roFk3OygXW7Wq9GTRB4c0sOWJA3OzoKQZyHdG6yB8+UqVyxblapVHBJpSJLOTZ4gkDrq+VlNAZc0oDp1bIclCEZ6HxCjH02MvQIhAAVCQ65Dgtq4JK3DoeGZ50IICFFCGeSA3dNhsvHM5oOU+pS4zrOEoMU9zVbUstW874efJ9xRtmxZr8/XrlkL8ZPGw+y58+CClDtAEB5eFmrVrCEKDMlzA1gSkJaeCSdPnQbXkWMsAQHH4OegS9euUKLELWKxZfMWeO3Vl8SSRmawsOelEAJDCOSDii/pYupedACfGCnNNYjNazNr4VjjpAfG6OwtWTJ88TKvC/EYPSUfmPOTZ4EhiHYT3qMpIMsxkYhTrHRvZTCz2lwjjhzq+eWaAkk6vAl6eh+0pwREAyHQTA6YkILaM2+IEEjeCDuz1GQNELZY5k4A2HNtZExzj9U8JreWEgJ721Zr7O07to4d9ZHPmX1yUjLs2rUDFi6YB3PnL/T6TokSwVCqZEnxL0F6RgZkZeXI8wOgYsXy8Pxzz0Hnzt3g3hb3qhKJ54YMgvET4/MUKZCMeryGWU8GMxgrKRTaQHtnNC1IlAxEnhgI/Cgw6jUIccC4yxkRpxjm3KmqQeZRUuDgRAwTJeKU4OPcu8Vx1LxYFgygcpEt3kg04k2QDGm0jCTEsAZUJyHQQw6UnnnNhED4fS9pn3tpOK/kuXHo8bIgvMikw+SkBnx4DWLMEAPLCEG/R3omdLu/R082ROAL+/btg6NHjkJ6ehqsci6HXbt3wQrnGk2/bdXybrivdRvo3KU71KhZA+rWrev3N5MmToCnhzyTJ0iBNNA6DRhwVc+BBYmIqmqIFhIksu9hoKzAKJ/VmzkuSgxcMsPKnrsjksckrxAjevxJoJADIJvVmyVOsTKPihJxSpS+Z4mhkIxWPOROKaGuxkg+jsEoIfDycIH/boigRggYL4CZagZsoKTv3qVLIO7fKRIx0O29s4QQDBo44Ns27dq/pJUMUFy+fBmOHz8uEgPiOSA4c+YUuFyH4cSxo5Cael58r1Sp0lC1WnWoUrUa1K5dB4oXLy68riK8rq3qFdBICqIDnVNgggwoDVrxoJBAx8TKeem9W+o1EPY3RjJmoTL2Gyc3OCrGycyDFCsjBvJzJ86QciuWLh0vOTevKHiNYhWuPS+PCiVOcSz5UPBIiLMUnqTRgl4FvJBMPQmgIezAiRDIZ4TxKt0Qw1R6HcRznJkiKfDvCXDkEonNAAP9LLgTgueGDBp88eKFcdNnzS1iZj2ZmZlw6tQpyM7KhqysLK/PS4eUhuDgYChXrhyEhIT4XR9JLNy2dRvYatkgIiJCjRQkS56CgMRFpVlekgU3jLsBimzwtkk3aAzw01Pn1hNBMl7+BqwjkkGUHxtPd7LXbJc5d3T9CyRiELAYurAPWmbJijN1zh6VBAXiJE9w5dZAS0F0yAbWlgnyeP5c8lmaBYRAfk3i1DwXJjtC+kLvvNBEiWksRSH3jtD7Rw42/8PU+M+hVNQSb4FwPI7cIgRh9evXPftov0eLyPMGXht+c0Lz+ICB0Kx5s4Cdjd/nzoW/lyxmcwZg4oRfgPVejB3zFbz62hv0v98I5yQmEPvGlBD2AmsEU1SFiDS0SdZ8wwnrdnA4F0plZFpmrEoeEYdk/MwaDa8ERMYwO6RBx2F1foGO/BIv4qSw7zw9KkqVG+ygCNL5sSQUlw+IgpdaoMxdb7fAQNPcGI98A9LvwAIjlSu6LpLxjwNr1Ch1GVDmmsZC4EICVPLaBbeqxNjXYDTHgysh6Ni+zYkVzjVVPhj5HrCEYPmy5dCpcyf3/xs1rA+dO3W2jByQaoIZ03+FadNnyPUH3CD7SEgA9S40bdIYtiXtoB+3z42kGcnQ0IGipkUDRbxsZm0H81LJtYy6iCUDkmCSEHm5+hli4AA+cfR48HaXU0KXbmH4JFo6P0bvBzVXP0+PihpxipbOT0Igkg7zKFHwOYOW9pU+8zwNtjupkLad52k0fXkjAnB9nZwnUOT+Zb0CDi2hY4mYxAJfyekjjHH3WAIRzuZGCJ5/ZvBb4yZM/owaW5YQNG4UCTt2Kjcb5EUODh48CP9bMB8mT56kui05SCOkVi3uhRat7mPDBgQnhKVhbtbfSoOpA7Rl/hp6oNlB2mR1gmEvgUSCYjkNhmrucjvwSbBTPHcW3wexwC+r3hdx4uFRUSROBgd9OuNKV5gBJUnv6xokc4koHJEaGmmdaVLvk9nnQSQEkhvbxWHm6vbI5aZ2i46wC51FO5Vm01xK9MwRLXn+iYs3wWLCKPSeB8lzlGQ1IQj7+qsvDk6ZEl9WqzHmQQ5IXkDC/HmwYtlfMH3WXN73Xp5JmLGQHCjV5FOXr14DUcaMEeAgsiQ3TLEqM1YeCXZ0wAlYOSYTpuAxG1FL0OTlUTFNnITBzKXj/stgSEISM/gnaSH1kpFhtQV4u6IH6a3f50AOKCEgv59s9j7PK/oDTIIpKziVTg1/ID27pJMleCb3+jqHbOJpEsd9CGPuWRvzt6aPZ0U1eZ4LIfjk449mPT/0hUcPHzoMze9u7vEZ6UKo1qrYKDmgeQEJ/1ukGhIwggrlw+HRvo/Adz+OoyfOZoWXgBl43TMduClX7NTwWyvIgVrpnR20hxMGaTWOxBuhFmLgXC6p5i63Ab+YH7dZscbzYwN+iaFqrn6eHhXFbWiY2Wzj+MglMmRBfOb8GQ7OUsZiLgET+3bCLTewU8P5MEIOKCHQqugof258JinKyJRdMjKWd1ck28srGggqoQsqR+20yPjbQbs6q69nUjF5kgchCBs/7ueUZ597Ppga6x07kmHf3t3wz+atMG7cBPhj8f9g6bKlYNR7QMkBgZn11ImoBdGNG0KDRlFQu3YEvPTyy1CyRDAMHz5crGTo1u0BqHNnHah/Vz1KNCzxEqioEcpvKCoVm+Rn1si7vlVJqc4G/sMJ3wi/idFw7GyZpVt+U8mYciyXVMuM55lgp3juDJLFyeBHgIr5Lg/i5CtHIpaTR0WzjoVKnwIrINcX8KtWKBl1+eL33hHWW8iHuzuZMSJOP02PKCF0+JkQUEKgR9HRXZ3ko68CNUZKidDtbyfBIokQ2GTXzsVx/TZQVo3kAcXkedOEYNjzzywZ/cnnXeWyxFPiJ8Px48fg3fdGut+jcf4tmzZa4eJXxID+faDZ3fdC27bt4Y477oCUlBT3Z9OnToJpM+fAF59/Co0aRUPtiNqiqBEtRRQuSKZwfmry9hIIA60L9LlD6Q2nKKVrgXSxe2bHGms/s/dE4Xt2HWTAaxalRg44z4p9ZcbHcnrovM6dTjKgRmjU1CmtJk5aCKHea6Cq/mhBEpwRj4JmF6+KSqH8PDWBm/HclRrvH6pTn+Rndu5QmRBQQnBDwzWPl7wBLpXtaE12XhAIL0EBJxk25ppaXbroReDMEoKwL7/47OQbb75dnH1z9+7d8FHsu/DDzxNBqX8BAYn/r1yxQnT9r9+4EczkHrAgHRObNbsbWrVuA4/06ePxGVFDPHTwkPv/RPToKccg6NO7Bzz9zDBR1Mje3i7+ZRIhxU5lnAmBmZPur68B78FbrfGN3Aj5JASS0XVqvMl9kQMHWFtSyGvWrYkkaSRLSkY7XkVrwGrixNOjoqhVYEEWeV4gCTE6CIEiGVSrVlCpf/dHCHyKGjGeR73hhlp5rWFcPiABuaVf4JXwaooQdO/aYWl0k+adPv3sC/d7RFDo77/+ggXz58DUGb9pXhcpFVy4MAGcK5ezzYf8gsT9O3e0Q4dOXaGdvb2H6JAcckJA8P23X8HaDZvgl/ETRAVE6iX4/rtv4aWXX4GgoKATV69erZaHCIGcHDhBxU3NORFNcWYnGQmyDZuvkIHwPTOxzHgLKwfU3OW81u9XoEc6hy4wLl0dpxAK4eXx8EWceKzfqwV3HiUEaiTBxZAEp5+B3w7mhIm0kAOaOBsm5S3ckN0vXhoFzG8dYE7OWLzfUb1QMxHg5dkzA4+EV1OEoF7diJxixYoV3b5jt3vWT0R+Zs6cCQcPucTYf0zMq9Cr98OqngI17wGtHli63OmVOEi8APb2HaFHj166ShUPHz4M/+791+O9lSuWwhdfjYFnBj8FD/fpL8ogEy9B74e6Q8LCJaquFZOEwGynNl2eAwu8BroS6QyIDvnaZryCOzsWrFfgM7P+9r7yCgySJSXjFA/eCo505mEVcTK7frE9MLtOKYeAdT3nB3LAHg/bRdFdTsZZqdAvOZC2SfcjXmkM09FO2fCsM5cNLgX72gbeqoXye4xL+2gVz5EDrG3QpfX+oUQ2xjQhaNig/le7du99jbx+NeZluHghE36fvwDOp6aJnQkvXrrkMYt/YsDjMOzFl33O4NVAhI1Wr3ZCo0ZR0L5DB13kgsX58+dh0z+bxNcXL14QXm+ApKSt8PeyW89J2/taQKWKFeG33xewP9WtXuXHQFo9A1KNYXMuLRPPDfhOfLMBf8lUNU+FlQp89EE2sv4jwrpsFpIlJUMh15ng2dOAN3HSlJDKZP6zA7w9n5CG9nQOYtHgrqkqgDmP9F62wigNsrJMkbkPlO4HXiWjXD0dEjkxKwCn1cgT0LHLBTr0FwwTgp4Pdt2bkXmhnpJ7v3TpUnDhwkXF35Ekv0FPPw8dO3UM+BNJkhrH//wj7NqZDIuXLNf8u6JF78jKyblSgiMhsIFn+UiUhTeIYntaznX/4iCgVFrGqPk5LDhOr1krZ3e5mp4BHUz1HI9i6EAKTdB4Le/B2UsrgbO3yBdx0jsDas+jYZRMfIjWZOcFXfkm0sAcIz3zVhEY1bBAACV2eRtT6sEICyDxM92jwSLiRVUVnXCrlDadV3mjIUJADtTx5OPHvo77rtTTjgHie1euXIGLly5D4cKFwblqnd910HCC3o6IRkiA1sqGunfWhn37b+UYkNBE5UoVYdYc8b6wrKSGIQh0sYK1K3oNmBwAszetX/lixlibjVOqeSrk5ZK8vCFqegZ20B4DFAVBfJ0jiaTZLSBPXjoTAZIu1nP+NSdgGhycKUmw5wJRyBDGjjCFferFPPPc+www0sU8Bbl83WPx4KNawcR1O2zBLDpdaTbNScGQx/m2TMlQxdNGrlu6IULQtEnjD999d+T7bBb/2jVr4cKFCxD7wbuwcdNWzesi4YShQ5+HJwc6DIUTfJGABQnzdCUoPvFYX+jZu68YSiAhhY8+/kzMZZBkjQPZ9MhXra+VXgOjbi3dg7mF5EBJfZGnu06pRbJWUqVZ4tlCz4oaceLhUfElBKXFK+H2MkmzQpvG7bJEPUlPmbCCroAVM1C/IUcLmh6xhCABrHNVu7uPWiHiZqIElSZ8uuhs2ureC9I9a2QCkgyeFSxOTvsjJ8G+PCyiR8QQIYhq3OBA8vZdbutNKgvWrb3pFXjqqScNqwc++7QD+vV/wlA4wSgJYEFKDT///GvxdY2aNSAyMlJMcCQtlsPCQvalpWXUgwCDMZx2C1x9al4DrQM4RXuTYjxWlN0ohRNswE9ox1ffBIePa6W7ERRzPXiGFdSIUyzwky5W65ugRgLduRY6ZGG1zgTTmZmWSwNJsIF5RTj386F3kNdR+6+FEJBzPpnz0CQSS6uFiDRKWCfCLXEpVyCbLhlMEqT769RLYDXct3Zm0XPPihNe3YSAuBtKlSx51ulMLEIz/Gk536FDB2DFsiWCAS1vSlaYuOoHPjXYbziBBwmQ488//hT/lilTBu5tce9N6nSr4qBMbjY8kgZUK9QJfXkNHH4MtaJ3QGrKA6BDlpkxfnofMF3GiXO9vq82w0oekCmS0aUzxiTp/CRpPD/+CAcP4kS3YSVxUvOAiF4CC1zFSoTIJZ1/vwOzTFeALlruT9PZ6tJA79BJCD22q7M3hL97Jd6HiFE0Q2RM9UBQITKsUJszFzsu6nlGEpn9dXLcB55epWRh36KNEIJnhT/jiKv/jz+WiGV/c+fMgVXO5TBvwf/gySeeAKJLQEsHf50yybCxpuGEl18Z7q4soK2NzUgYyyHM/kVJY5L78O6It+C+Njefo27du4l/SShByj/gXX5IXc30pk7SqWxnBTnwpW8vfwAU4+LSfs334RoTHw4NOQdW6Ci4k+A4x9EV3eWy60yN38/C8rzKwMGen/QAelW8BKg4e1QUiZO0HdbguSjBzAXFQl1SxrLGMnSJUvMOMD0J6POu243NkAN/3js5ITBzLlVFjGTeDPk4ZIoMMXoUtKQ6ITelkZnr5y80SPVhEsCPFLVBckjPNde8E1FeWy8hqFc3Ys2+/YdaU4Nd/647PQz+5k2bvbQBqBGfNn2GYa8BqU7YvnMXNxIQHdUQGkbWh5at20Lt2nXcqoUERLmwR8+HoU/ffrB+3Xro1LkT/Rl30Q1hMIxXGHA9BE80Nj3ibTzVFAqpERW3p6KWqDVm6fHgqBlAzoabnt84WdmiA/hJF6t2+hO201j4s1pYQjSSM/H8+NEx4F0xIveo8CzpVGykxR4Le96kOvrcrhJgVQpdGgSIKDlIZ42oDx0CtnOfCzTGkX0YYiVCoNfj4k/ESOtkxLByoRQ2is8tL4DsWP2NrfRZjbegjbGaN403mhghBKfOn0+rSPQG5ChWrBhkZ2f7/D3pE7Bwwe+s6E/AQEhF2bLloPk9LaBChUpen/ft28dDP+GlYc/B7Dm/sySGqx4BMwhqYe+JzMzRGcCZo3uGoKY1INu+3oFHvh3VZkcWEB+vWStHIR96zeRlf0puUK2G1F+zI97X3sPdz7EihSUePptBSbNwJ+SN0kG5AXAxHh0tuQlqhMAfEXH6mmky0rcO5r71mp1rSC70qWdgUMTIkjEzgEQgzse9foQ5Xy4Ltm8H67ULWPQ2EjK4QQR+Pv5oFIyJ+1YgCHXg7mZNoFoNGzhXroD1GzdrWg+J/0/9NR7mzfud26xfDuLB6PXQg9Cl2wOioFFISAgsW7pM9fuffjIKNm1OgiwVUlO5UoU9KSdPR1qxr5JLPl7HQLsAfDQ8Yowzz2Q08gD08tOBkZfQjr9OiDbgV09vdRzdHXuVFh5lkP7IAc/9V0pAdAA/gSufzaDyMClQm+k7VGbVegmB2qRAtekRk+RmkxtiycDNV7uXVPoa0PUZ9c5Z1kbehKFly+5scKua5Wbp3c3P41SeHV0iUAb3jSfp1jU50kUIyM1xf9cOexYvWS42MyJ5AqdOnYKjR47Cjh1JkLhyGSz6c5nuPSEtk+f/PptLB0TaKvnxAQO9QhesUqESSPfDRX/+Bd/EfQOb/9kAJ0+egGLFiovdEv/dsxvGTZgsxlmsvCrCQGvERep2V6kZa5Mza9WeApz237CHwocQERXwcEkLq2wW6uM4KTFwWUA8rDJCigmhzP7TASZUZlwAbsWz6QDZzt+gAZ4dMHnOYnweixQHj8mj14GenxgfsXazhEC+LSf4kS5W2AdKVGh829e+8iKUlioXquw7gfyvr2dflFz2QT5Fb59Vx2FxX4MjzDjoAkaDwVS3wxb3NHuwTkTthaRlMMXGDRshLS0N/liUAIcPH4TejzxqWGyIEIwp8ZNg8uRJurwGvXp0g7b2jvBQz94+tQz8EYLf58yECZN/dVca0EZHBKRHw6uvvREIQuA0OevS0g2RMv50aVECvXmcekoKpfwBu0WDNjXYasdmlx76BD8CQGpGkoVSHD03mLveax+ndPwMcQKlxD6d3gWvBEoLiJPPplBSnD6MGejDdAz+vLFAMszxGgZ9K6WL/ZIDMqnzkyhJ73GepF7MYOdsQNnSUDrLNzNuDpfGFpYMuGW6LQoJ8AzxeeWhgAGhJV2EQDC830c3vfuF2FEfud+jgkSzZ06F+KkzxPdYV728BbFWkP4Fv82apli+SNd/b8vWuhonqRECUi65fu0q+GfzFlGpcEr8ZDHHgCUEZH+k5ML2Vma6cu5z4JMcWExs2JpYK2JgPt3MGveRJsv5yt/wKpvjmGdAcgmagjWucM15H36IU7yf47SKOCUL6zRtRBhxFtZDZNN4zmmoRw6qa6BrwLWQECh6WbS6tCXDxDNpVwmGxk2Fck+bRc8LWeev0l93CNEisSWz5DlRZvj5aRnoIQT9HumZUKgQ9Jw991bjnyV/3kwO/OijkbBuvbexpY2NlFz4Wr0GpHyRJCLWjqgL9z/wkOE+CCwhICGO7UlbYe36jXDYddTje6QCYfjw16BFy1ZuQvDlF5/Bm2+NyG+EQNPsMUAEgRVXqsl5AIw2c0waE/2U4ujkwY4F49n9Ys291eJTZg2rSiWMEgGJUyBODhOEsIxRsqeTLNgZssA+e9w73skMnB2s0+b3u+8MEbAyDKNL0limY2CVl4fOpp2MUY2X7oFYC8MCRiYSNBxMDX8Sx/2xy8iWPqXCju3b7F7hXFOfZOt/+8M4cWZOCAFpITx+wgRIT8/0+Xsa3zfa9dAsJvwyHv76cxEsW5nod18Jnny8H8R99xOMePM1GD8x3hTT1TH42pkHwqokKsVWuQEkBzbgV0YzyJ8LnCMpYIlVvKyhkpFZsWKXP44Nj8jAZ+fhHdJICtz3FqeGSr2VPByycIEHeDybDFGwBSL2LVOY4+VN80kIApCPYUjSmJOAktJz4AQVMSOp3Xa6FdfaQJKgJSqGCmRLiZSM0kUIGkTWO7t7z75w8pqoCbZsdR/Mnj1bnGHLWx77A/l9z14P+437mwH1LqxY9heXhMVAEALZIBzGDBRWdMPj0mGOAzmgx6d3MNTUNlfHvujRfFesp9eZ3e+3B4RMtKdmbl1f6V5M0rEPXgmIDPHSGjP1yiPQ6XanyVQAjJufLlbEhTnO3MxOCvwRAisML4FhSWPOIZVkadKTK2qGOhocJTNEJYHzPoQxY6sWz6M+QtAkutHFjIzMknIXO0GRIkXg6tWrhnacJAX26PmIrnwANVA5Y6KcaFTrwPHk45C4eo1XKMFWs/oN15FjH/IWJzIws+Y1k8h1QmDCcyCWM/H0cJjQUPASItLqNRB+U0jH/ukhB5obKVngRVEiTvKGR1oU97wIkwVxeEoaKGFwQgAa4ej0VtABXY+r2R8hMHIt/RnfeKUZLSNiFCZ83svHPmn1QqnBXaqcW2WOGhsc0f108ialTKKikQnWKL0hg7R33o0NS09Pg7+XLIaUlONQq1YE3BXZEF548SUuB0TCEaRSQU8yIlFCXLgwAZwrl5vuaUA8HSNHvgeNGkWLVRN/L1kkJhiSpkvff/sVIRmjcosQKMzY2AYoRlx/PGeQZOCyqXzsMtjQhz5cNbXMHjkdh5lByUsBkfEavCosHYSlpOw3jwnLEr3ERkNPgyZWJJIK200H425mvQ2PvPIfApSY597fvCSqo3Ow90cIwiQiZPRauhOWVUSM1JQMm6h8n+xPWj4lAf6eRXrvJ/D2AsjOt8PkRNEYIaBJfceOHYNdO3eJr7vf3x3efusNOHbkMBf3vL9KBSt6GhCQvgbvjBghEgK2wRGB1OSot1UXlRM50HND8CQExDhr0UqXtyX127+B6dnAGupaViRH+ujDoHewlCsgOjXM8NjZqgs0yFYz156dlXDJ0FfZntkuhPQe0NTwSO5BCTAh4J5UGEByoCWpUO+11CJi5E8ITZFkSXF8rYJm1CORkFthHyas4+tY3ZVQebRagS8hoF0OKSEgKoDkMxq737h+ramuhxQ0GbFV6zaiZ4LHOrUQgipVqkDjqMZyQhCIKgMbeApIuEBjx0Cd5CA3CIHag5ME2noakJs/mrc7XLYdXv3j3e5yMKe0p1W2mg4Q5F6Js+jcREvXiZfypVrDI5EcyI8jPxMCDb0MADwFZFwaexooPfNaCAE5x4c1XCOnr9mtRjc5e6xeyoUachrcGiS52OFQS/8GS5UMDZxvawnBsBdeCaMzdjVCIAdRIiSGfP3GjZbJFJslAY0bRkLdO+tCUnIy9Hu0v0gIWB2CABOCdhqMJzUQLj/kwAHqMXmehMDJ8QZNhlvSvLny8HPu9McbCxjy5Mql82OXzg+Pa67aKVKHUc3PhEArYRY9ar4MDUMObFpCmyr9Dfw26jGpXTBcWG+cxvPCTSGQqU4h20tn98EHYdKasxUI7QIH8K0MoUSUTjydepMK06MbNw79Ou47Mflv6q+/wqaN6yB5ezKsWrMBvvj8U3jjzbd9roO6+rds2WQ63m8UtNNhlarVoaatltjtkGLYsOegUYO74L627aF9+07Q/O7m4j67XIfhs09HX9+8NbljHtMh0Nox0AbeMfm8Sgjkx5cr4kqyWbcD8qZkrtt9mkv6EnbgK7mq2inyNiYESgO5+5k34zaXZr3xdF3+1icZJrNEWZQJZtYZD95t1alxdRk8zza4pTFhUyAt3wjrjlEgOXaGBNTUOD7F5nFJY7YRl0/Pky5CQDod7tt/qKLa5087nhSlf7WCVgQsSJhnGTkg4YbGDRtA1Wo1ILx8eXHm7wuEEChVURAUKVLkxtWrV8tambzCwbAmMrNrl59BPI6XkbWQEMgfPg8NAIuugUMaROJkWgNWq7mZNmAg0wCw6PzQ+yveQo+K32NR0CNgjTf7mdH7Mq8SAtA7o+e07zw774meVlkyoa6YO9OkyA63xHW0Ppu1pJmxnVmidN6fsVZMDhkvT6yBsUZXq25ThKBLJ/s/S5cn3q32eb9HHgJWxVAPeGkGkBLGqCbNBcMfBdFNmrg1Dkg4Q0tZJAl9+EI+6GWQK7NHRqrYBt6Kb7xhabkkkw/h1jKXaQ04DD6sAYGeUkaD5+eGGkFjiBMv1ya3a80QCDp7DGOIQ1Q+JgRy0pzAixxI+xxrwfO8gJQgSsmE0aBBu0DyTtgZAmA0J+e0sGQbfH6tJAI20OeN1BxKsoQQNG4UOWvHzj2Pqn0eWb8u7Nr9r+kTQ8jByhUr/CYQEnGjenXriT0NoqKaqEojk46MSdu0naseD/VQJQ7C8aclb99V1sqn2cKZdsBdy0yzIfoQ83K5W00IlOKqStK8PAbLRJOz2NwkBBRKXSLNzHICdq0VBmR2CZO7lTkQEicEJvRkisxYSATc94ywf2E6CIA9lwm4lURAq6SxW8QIboZ2eKoY2nUTAuFHDwp/Fqp9Hly8OEydOtVwQyM1kMZCfyz+H5w+lQJ16t4FbdrYdfUzoB0Z/eHixQvQt18/1c+bRDf6c+u27fdbPNiSgdXqRDZ37W4gpYsZL0IvkwONJRoEGkmZkjSvVlUyn8fCUba6jMUhFV+DhpJIk5lmUHlKPIvzAGyDW65u3obXECEIABHwmSTISaXRFy4IS2kd3zesvOjnPGsJQXLLFVHZvrx/ir4qA2lF9AdEp3hvSEjpq6EhpYsLs+rQk6fO2Oj3qOter/HmjczMTFi3dp3f7505cwrWrk5kexZ4oEiRItnCMdYPVN2rZBzoYlWTj1wdbBl9Ab3s32pCkKRhMPKS5tXYVlmOQT7K7tjBMTQvXFcdao5KXSJ1Eyc1b4cscYy6/rXA3Qte9jopt4RtZMfEy6OmmxCoVBzwAA1jKCYJaizn47F90YulkexMAQvaHmsQENLcytqC7esnBH5uZtX4WG4RBCXvAPEEEBXCfXv3wMmTJ2Dthk3uZkf3d+2wfPGS5Z3y2oxCGkx9NabId4RA4fgckEuyvDpmwEoPsJI0LyUGUTyuAUOetAyavc20PdawH3qEm5REmjQnaOaCMBEVh3JJs7L4XCQIZjxqRghBPPDzTvoTMbKaBFBSGsduX9iuL6VNU9UNfoywr2O1mgRokQnnSwhk3gO/CARBIDoJ25OTPYz/7r37VasICPr0frD7nHkGmyAEfnZtB3NNj/KkO5YhP2oG44iw37Y8YvC8ZhWyBEQ6K1YbDHRfAw3kgGvTJ9m2jSoVuuu0ZcTJ54wJlQrdx623JM4IIdDq/TFKAmzgX8mQBxGJ9+GNuOGL1PPyEmkkPAukcxVv0T1DSYBWMsmXENSoXvXoseMp1Y38lgdBIMmI27Zug9WrnbBn13bYtCXJp/GXo1zZMjfOnU8tDPkMTGzeAfribnk+PuvDc2CVVr8l0rwqEsMEpuL9KuTASsLkAvMtmZUqN2zSMbDNoALR3ChfEAIfsz47cKyQMBA24K1kaMazEws+Shalc7ZNz290kimWsIXKtkNLASnirQg/mxQw4ksIateqOUkwwIN4rMsfQWCN/4F9e2H7zl2mVRCbNWl8efPW5JKQj6GzYyDv5kYODV91SUu6XoMum20nWBE24FxP7x5w4FZsmICQg7ukRT47cLfpNdAQip1tD7JCj4CzQqFaTwNq7EDu6UBCoGoE5M+8maRCf+c3mfEEWKFkqAcLpJm9U8excVE/1JAASc5TjJVCdjKyE2Ny3OIeMhDdrX1694B/9x/gKlNMCQIv46+EgQMenTNl2qx+uWzQyQNkUzGiosHQOqPUQA54EgKj3cpozNZJWbQWQ0iMn1VxchnB4VFPT2bFJAz1qIHfsipjTtDWDEpMsrO4NJN6pLgSpwIuXSxPfpQLK1GwyY4uPTNJhhzYjJZMCuuQJ9V6qKH6mk0zRICnxK7S8xQPOmP90rkJM1qvz+R02DV6UWpZnYSuo2TR17mk3osEroSAoGTJElm9H3qg+LSZc9w9DKxsRsQLTaIbwdZt2wvl9n7o0CHw6BqooSueDbzjd1xDBhzcyfIByAkB0utnmvYYToALIJJl5yc9AOcnVhoI5aEQnh4VLz2DAkYIzOw7S5xFgmihKiENQTlBY7lbgIiAWwhLo5KhDW555nQnCsoIgF3ncY3S0kvCBLGkk5WaOp+vJHbyJT8n3AlBSEjpGRcuXHzs/PnzYr8DAl4qhDxBGhp1at8OakfcCXff0wJWr1p54pvvfqyWjwiBYUNhhXSxtF6ry5acVngFpPORwDzwvioHYiHvKRRa2gxKoZNlsnRulIgTL4OwQFh/L5VB3qFjPfJZuJ4S3ryuVEgHeDpzD3ivjwARAa9qAT8GnP6lz6lH7wQfx8H+1ugYbEm5InPv61EyZCdWmggkd0JAb/oxX38Jw1993etz2r9g8uRJAe98SJsatWzd1qOh0Y4dSUSdsO+Id97LdbaSn7sGmmyBrGcQpI1YEkwm5IVJBv4VP9uSJ8DZwVrxFh7kyXQzKGn2H+/jOL0qBzgqFFqWGCkzIGHgqWPAyhu78pl0MStkk2ClrkKAiIBPUSAdM/jh8s6GjOaDnDwYPe/Uc2EFEbCDtj4SHp5VQ42heBMCgpIlS6RE1LZV3r5jt8/v0c6H06bPsCyk8EC3jtCgYZSwNIIKFSopfmfDhrWXY0d9lCeSCS3uGkiNaIKP7TvAM4fBBRrd9pIBiZMG1EAZyyn+jklhH2lZo54a6CmSkXUy6+KRyJOnyIF0TDSpT+s1VHT1S/eSw+C9YKnWRG6gICREBoAIUJLpZVxV1PW0oAwlRwr5EWYxCixoeawjLJDIEEDTZMQSQiCVmUyeOOEXGPz0EE2/IfkG83+fbTqkUMtWA1q3vBci7qwHLVq09vt9olC479+9P4z+5LMXCzghUJr5KoYMVBLGFDPCNRhfGxjrRmbFMcVz2H6itI0E2XE6dA6S30j7YwPPjm1Wxl/jJXLgUvHu8BjklaSLle4nf+htZdJoLhGCaOkaRAVgc1YkRFpJBKaAun6BQyIARsKRYhMlZl03OO5vbigZisdklRfIEkJAEBJS+pStZvWKzsQ17lwCLaD5Br9OmaS5JXLb+1pAVOMouCuyoUcowB9IqGDzP+uvzJ67oFheGTSkWVUvyVAEYuCgiTpeTY8YQ+dgDCm5GR1GXfWSS9kOxlqO6j0mrzbJJnX15duIBU/pYj3u8iYqxIV1Y9otIlCKrYWl/dcyK9G6DaUERC0x0Azhd2EcBldKSLVIG7uAqeSxWsaYqTiQk2ZexpYLIbCYCKgaNpP19B7EUqZUaNbgcScCGkWMdLWGNkBUyXl2WUYIqJdgQP8+8O0P43SRAgqSb/Dj99/C0mVLPfIN5AmBpUpp71Vx6NABWL92Faxdv1EULXrisb5fTJ3x21t5dVYh6xho5QybPqDxSjMzmSFNlkhBEofj06vAxuWYOJbNqSUg+iIemuPjJnsaGPaq6JBe1kScFBIQfREnXeECxrjaGSPLg2gGXIeAyYw3m9zGixCQe2BsIEiAtD1ez6V478mTCYX1Ow2eU65EQCMJcD+fViSMKghGjbKMEBAUL158Q05Ozr3kNSEGHTp1hV69H9ZFDki1woH9B2DVqpWi/HCTZnfr8gIQkLDA5n82wOq1ayEpeaf7fXvbVhkrE9eGQT4CYyCsnEGqln8xZWaikeKdrGhCddGQ14A5Hh6a6krSxUrrNywtzHRE5C3/quY1sAOfBEo16WI7eCdM+SyHlcWSoy30pOUJYSLJSNp1EgSeHgKXiWfDIwnYh4ogLwLKwqv0T6cSI7dkQeae1ULsdZVXGvT4OBTGD2sJgYJUJGglB5QIaGlbrATSwGiTQAL+Xvq3BwmgqFix/PVTp84EQT4HY0DtYE3Jny/3ss3K6gVmJtmL47GpVQ7wdI0ukAyfU+FYYiQi5eJ47XmSJ3/EiYdHxYtsMuEpcm6i/RjH21qpkCEIvXxcd277LmyPXHc91UPJDAHwR+ys1PiopZCYqOVYuEgaG2jlzEVB0Yct9pcAbS0h0OJykpMDs0Rg5YqlsGtnMixeslz1O1UqV7rx4P3dhoybMHkSFDDo7IrHxWsQoOOyghx4VQ5I23IAH70BRTJloedI3gvA7PWmxEDJcFuSgKhxkEXpYv8zT56EwJ+XwEP/xJ8RlcIiPMilL3yjpNTo5/7xWeZokSfH/RwEKCwAuUoIpJ2K13LxiTxx3XqRuvMCNmxYC7t2JMOylYnuNsZqKFWy5I3OHdu+N2/BH59AAYfOlsK6DR2Y1AHgYPx4zYy9KgcYYuAACxIQ89l1n+LDo8Jjdqe5ggUJgd/zQ4kBkeh1cFwvO7PWRQBk105LPb0ZEit6/3y5+GWJhYaS9WR5K3YDY4QlrZZNel4CQwgIqIKh5kFN0g9QIwfy5EAtIGSgVcu7P/tr6cp34DaDReTAV1KaTbrh1TKnqcoaBRlcqIa75sY+zHE5OMxYvRLgpG3YgU8cPZm6wzVUO1CpWmDPi7To6WdBZ488ZmNqzYh4eVRGCeuORUKQZz0R0UZmzxblB8ifFT2SxnHSc6S5dl9yubPJnlEm9pUSAd75AdTzotU77KVkGDBCIO1w0oD+faKWLnfqEiKi5KCmrRbs3b0TFv3xp662xgQvDn0Wvv9pPAjHWyivP3waJICTJSNhyJByNqIUTRRIgRPMN91w0r8amvrwGnjUKgfoA2fUuLqT5aQZtsvE+WdbqmrpZcFzRu8lXayR5Pg75zYDzY3kxFIrbBrOgxW1/HbwLIG0gacQmBqBVnvmLS+RNHGs9Hm0qjLKlIvfj2HlUenhNdmwKD9A63PHKlkqKhkGmhA4Pxj5XrvHBzwJLw57FpYuT7R8m08+3g8++PATcB12QafOnchbZfLiA6STEHAzpBxzDrxmd9LMmudsTm+vBh4JcEoJiDbQpylO4KXNb4HUcyJzbpx+iJMDAls54A/DhXXEaTQ0Nt7xVkazgBplkbDxHMAt9G6wz7wzN0lCAASMkuGWkqFi2aIegiBdE5YA8BaF09SHwULCRcfM+FzpZaCFEMSO+kj8/7SpU+Gtt96ElJOnuG4nPLwsdO5gh27394AWLVtB3bp1Yfmy5ZQQtA9Ef2qThIBc6MmBNKRM0p5RQ5EorNeusF4yyL9i0alyy3aqqO/ZgG8CXLxC5YCWwY8M2NEKJZxh0jWxwpXqt+cDR+llX5UDWjwqivdOQUOAwx1TeOYQaCRUekmyHuKZoGbUGO2CXtLMt5eG/eU9xiqNTbEWeC+0ihiR51G3nHFACUH58uUONI1uHDFz9u8e5YYfjvoAVq5YBus3boGcnBxD6y5dutSNB7p1LtSmXQcPnYLaEbXh2NFjEDfmM1j057L8QgiIoUizcBMLGEOhZkjlrZL9PrRKYjsWGz3Fh0DlmBxgUeWABqEd1dmvZJS3BeC2WsCQp3SLiZNcutifsWgSiOZbtxkhCEj+g4UVAxkMCXCqbJd6uthnrreW2bj0+8NWEDHgHMaQ8hccfsgWJU2mkhQDTgjOnUuNqFA+HH788Sd4pE8fscxw0z+b3N+ZNWMKLF7y93nhe3PhVnytOLMaMpjtFZZsYVkivQ6rZauxfODAgYVLliwJjRrdDNERQaJlf/8JU2f8xu5GnicE0iAaD4FpmuPPkGrR1hYh/L6QD6PHCsmEBuCY4lSMnx34Ce3EyrehQDz8zn6lc0zPTSCaQqmpN/LqVOieIWnwqGgKFQTAsCnJG6fzDE0UJEJgERFwtzlXM+p+tP79tjmWrYuX91JTdYMFngD3s8wrJJErhID+n2gQlC1bDpK3J8Ox4ynuRMEyZcLSUlPTypp50Ii8sUoJ4mPCMc/KB4TAJt1kUQHcrJZZpEPNWKgRApVjiw6AEfRXBcFjQFNLQLTTWbfeUkNZPwMrlfgUcwAYksKt54OCR4WcG5tRxUYTBplKG9M8gahAG1Wm7TKAZ58Fu4Z9yiuEgFfXQHeLdjXypSNerqg94IcEusBcYm88cKgYkAiWHbTprFhXshhIQlCtWpUDJ06cjPD3vfDwsufOnj1fXsfJfFD4s1Dj12cKx/w45CNIBkJuRK2cZbvddUrJaSrGwlRDGsmA0gfCCgPoS3GRVxKUV70+p+tvdb8Huu9KIk288gxUyYdFBot9VoySqgVa4tEW7r+ZZ95qQmDU26FJypgxkg4dz2Yt3THzmzPx+UbGEjMJp0zFCV2iND5DsWBBgyN6vgNKCEqXKpU9Y8aMYpMm/AQJC5eofq9q1copx4+nVNVxIP2rVK40rUKF8CAlmeJGDetD506dYfPmf66sWrPhU7m+dX6EbJat9YYyOpCrdQ60wa3YcBKvxDDGdW0HaxQXlRT4eJZJeVUUWHDt6fnpacH1jgXvUAh7rUPNnn9/egMmCABdeNwzo/LSWMHMIu0aiKHlZEajy52WuomLpkx3Y+EIwwRIY38D07NyE0qGliQoMsSEPtfxga4yuEG3R7L+hw9/SexiWMtWA6pXqwJ176wLhQsXhhXOxMP7DxyqredE29u2+vOtt98Xcw1IW+NjR1yQlZUFjz/hgPYd2ovf6/1Qd0JERhUEQuBjFkmNqBWzSF+x5zCrJI0tbOjj1XNA2h4lBkZJ1qBAyBVbTJ7UKgfMelTIeu1mkwiZGZaVXpPevMvFAkgQhgv7Hmfx9pVc7lQfQzMBMEkE3M+c0Rm7dBxOlefdUIye0TIwM2GzUtKYnmt2zBgVcELw7NMOeHPEexARcTNysGzpMrh69ar7O8SYT5w48eDef/fX0bFeD0LA4u577oZy5crBls1b4JlnBsG2pB0FkhDkwiwyXj7LDtBxWaG4qCa0Ywf9CYgBIwMq58eKXha+iFOsjuvAiwyQ7U4OwOnM85olCoM8feZjrTAkCtuk2yP3RpKR2TMHSeMMYbthJo+DJTc+WzT7OAZebeq5tlpWeHYcKmNa4AkBff3ByPfg5VeGw/59++Hff/fArp074NDB/bAycQ0UuaPImVOnzlTUeUOt/OLzT90VBhQVKlSAcT99B+MnusfoycIxD4bbCLIYNG8XPHl4YnOjbIyJb/M6Jn8Jgk/5+a1D7j3J5etOiRMvQqhGnLR4VMhvuXR5DFC2fq7lD9wukK6jXsKtBF3JhH4IVbqG5kzU6JvJTwkYEdChERE4QiAxMI/aelJ+WLJkCS8ZYuH9I6fPnLUZHSDa3tcCalSvDtnZ2TB3vmeuYXDx4ocuZ2VF3M4PogWzyN5mDKFk2CnDTzdCLvSUR+p5ODUK7SRLZCDJoutlZ/7r0mtUZa2XeQxevhQKlQZ4ci5jeCYTEpEzsLZEM1+UJ+dTIsCrgoWilkWzafK825hZvw2sydXiTgSYLpj+nnm3Jg3ZfiAJgb1xo8jFDsegEls2bYTps+aqfjcsLORgWlqGrpCB1hlDiRLBqZcuXS6Xj2f6akzYacRgcCAHU4TtOTjM9OMVblySTOOSFnJ8SRr6GfDWUPdyl8sS7LgnyKnM9ONk14fK1dKmR0laugVyTA6k+0CJgUuBGERb5TWRkgi3ye4Vqu8P0l/2XnEparcr6w9AbpEBWUkiSMZICeyxuqwwiBYcmwP4aFx4jBEWlYaS/fzAwtPBXbuAOce+vIJ0uwlKeREBJQQd7PfNX75ytXizp6amwm+zZwEhBwQnT56ACxcviXoEgsFOPn3mbDRPQkC8Ebaa1WH/wcPHUlPTauTj2T254Frip9SYJukwFnpn2e7ufRzJjr+HMBluJS0l+OnTwDOkoFi2GMDrbpNIQU8N+0l7WCRouJccnGZqXgqFATKe6fnBGKrMPum9xGumnOfCHCZa8Wom61aRN8muxHPeb3dYkkd+iiy51tc4pyk5MqCEoEsn+8K/lq4sRd+TqxQS/D5nJqxMXPXXgYOHu+klBHN++w0OHz4I586ehdTz5yA9PQ2imzaHbt0egGbNm4mVDYMGDUw+euxENORjSDOwBANGjhqLBD/Nb+gs2+HD3WTaM+DD8BF2rjXT2N28Q80YcfYa5KruvnTt9QxSPvs9WOA1GGW1x6SggHNyJHkO7HklCdJAK149s2onWFSL74PQmNUp4SliFMYQgJ5+tqm5LXSgCcGDD3bvtHDhH0vBHyFISk6esmlLkkPHukVC8Ocff3p9RqsMCAgh6P9Yv/SzZ8+Xye+DiWTk4sCcYIzPngYqxoI8lDFWz5QNKglmMMYvwYdBdRg4b16Ke3nAU6R3dq+FPFHipDdW6iVVjNA0dvWSDEWoyefYkRfIAMdEQfk9m5CbOR0mPB3JEgmIN7n9aIYERGl4Fg11WAwkIfhe+PNCrx7doHZEXSgdEgIREXfCqVMp4ud0Vr9uwwYoERxsiBBERzWEqpUrQuXKVSE4OBiq17RBVFRTWLduNVzIzISVzpWk7JDEBwsVlAGFo5KcFmNBznNSIJTmZMTAYeBBpPFtxePR2NDHL8HIQ9df70zMXw8LLcTJ3YXudmhOZLGxMULuRZLKs0WzSYOVAOY9cKwXwJkXw0FMnwG7yvG6JdONln7KpIztGp9t08mJXAnBv//+a1f5KPqFoc84lq9crWnWMaB/n+T3Y0eTg9JUW3r61Ok97eztnte6n3v37h0F3klHFOn16tXLd4ObCcPpa6CPC7TOgAbjRx+QdjqPJw60dUJ0t4rOqyTAx/lhBYr03AOq+REKxCmR8SohCeBraGzM/a1mBGgOTUJeEU0y2RPAiJKheI/zKDXkRIToYgOd+gWy9djhlpaBnueXW5WCIiEQDLtNOjiAW1mu8mxcXdraH384Ut51UBUvvzgUhr2orwnVXXfdpfm7AiEwMnumF5jN7nW/FkiEM68MLNIgbgfPWtlQHcfphFvJiHmOoctmsazmu03Dg6QoslPQIIWU2EEmTMN9oFg1gED4MWaEMGrNhWCTgpN0Khna4VY4osAIzKlVumgE1wqTQoJxZFkpeW2JJv6no2NhyjRtTQZjXn4Rnh/2Yl4iBHrYLi0FcwokIc/NMGU17eINVRAHf8Ygwu1wvAa9LUoeuICGhBAFwqC5QN117pQRgHQD6yeEwwGeXsFa+bG6JM9fS8E4usAaHXAPjPnyM1Yt0CdI8l/ValV1rV8rIWjd6h6YOOnXQJ3f4QIpiMPbDIFAFFAyQLsFHmEnQzxmrj50C1BF0kJCwDbF0ep21Y0Tx0/A8ePH/H4vJCQE6kdG6l7/xg0bNH2vfv1ICAkNsep8EneYS3ooEvJjLgICgUDoMNo2CxT2/GXz5+mmU/n6eqolFarkEchfE7QrwOfniGTgKVzM/z1U0QTjj25WBAKBMEgsQJsWxhHBZtnwjAWYEJiBQCbU4pNqpCIQcMmMuxxo1BEIBCKwRMAO+nRBbotutQWKECAQCAQC4YMIOMCYABYmE1qIIngKEAgEAhEAEmAD/2JgvrAAyQASAgQCgUDkXyLAqzV5PJ5NJAQIBAKByF8kIBpuKaea6dPgFjLCygIkBAgEAoHIHyTABjdF7ggJMCJwR4XdnGBCyAiBhACBQCAQueMJ0NqFT834J0nG34VnFAkBAoFAIPIXESDueztoCwewKoZo/PPydcWyQwQCgUDoJATpCmQgQ2b4iXyxE88WeggQCAQCUXARL/11MbN+jPejhwCBQCAQCER+R2E8BQgEAoHIc7PVm7LGCCQECAQCgbgNSUCYsMQIiwtuli8iAnn+MWSAQCAQiFwmArR0kTY5IgmK0ViNEFhgUiECgUAgcpMEkEVesRCDZAAJAQKBQCAKJgEIg5vaBWokgOIbgQzE4xlDQoBAIBCIgkMCohkS0E7DT4YLZCAOzxwSAgQCgUAUDBIQC9qVDBPhpp5BnEAGkvAMIiFAIBAIRAEAMeoCKaCzfLblMdu/gBCAJCQAeQv/F2AAk6lJiTpcRvkAAAAASUVORK5CYII=";
        this._logoTexture.width = 516;
        this._logoTexture.height = 192;

        // bg
        this._bgLayer = cc.LayerColor.create(cc.c4(255, 255, 255, 255));
        this._bgLayer.setPosition(0, 0);
        this.addChild(this._bgLayer, 0);

        //loading percent
        this._label = cc.LabelTTF.create("Loading... 0%", "Arial", 14);
        this._label.setColor(cc.c3(0, 0, 0));
        this._label.setOpacity(0);
        this._label.setPosition(cc.pAdd(centerPos, cc.p(0, -logoHeight / 2 - 10)));
        this._bgLayer.addChild(this._label, 10);
    },

    _initStage: function (centerPos) {
        this._texture2d = new cc.Texture2D();
        this._texture2d.initWithElement(this._logoTexture);
        this._texture2d.handleLoadedTexture();
        this._logo = cc.Sprite.createWithTexture(this._texture2d);

        this._logo.setPosition(centerPos);
        this._bgLayer.addChild(this._logo, 10);

        //load resources
        this._logoFadeIn();
    },

    onEnter: function () {
        cc.Node.prototype.onEnter.call(this);
        this.schedule(this._startLoading, 0.3);
    },

    onExit: function () {
        cc.Node.prototype.onExit.call(this);
        var tmpStr = "Loading... 0%";
        this._label.setString(tmpStr);
    },

    /**
     * init with resources
     * @param {Array} resources
     * @param {Function|String} selector
     * @param {Object} target
     */
    initWithResources: function (resources, selector, target) {
        this.resources = resources;
        this.selector = selector;
        this.target = target;
    },

    _startLoading: function () {
        this.unschedule(this._startLoading);
        cc.Loader.preload(this.resources, this.selector, this.target);
        this.schedule(this._updatePercent);
    },

    _logoFadeIn: function () {
        var logoAction = cc.Spawn.create(
            cc.EaseBounce.create(cc.MoveBy.create(0.25, cc.p(0, 10))),
            cc.FadeIn.create(0.5));

        var labelAction = cc.Sequence.create(
            cc.DelayTime.create(0.15),
            logoAction.clone());

        this._logo.runAction(logoAction);
        this._label.runAction(labelAction);
    },

    _updatePercent: function () {
        var percent = cc.Loader.getInstance().getPercentage();
        var tmpStr = "Loading... " + percent + "%";
        this._label.setString(tmpStr);

        if (percent >= 100)
            this.unschedule(this._updatePercent);
    }
});

/**
 * Preload multi scene resources.
 * @param {Array} resources
 * @param {Function|String} selector
 * @param {Object} target
 * @return {cc.LoaderScene}
 * @example
 * //example
 * var g_mainmenu = [
 *    {src:"res/hello.png"},
 *    {src:"res/hello.plist"},
 *
 *    {src:"res/logo.png"},
 *    {src:"res/btn.png"},
 *
 *    {src:"res/boom.mp3"},
 * ]
 *
 * var g_level = [
 *    {src:"res/level01.png"},
 *    {src:"res/level02.png"},
 *    {src:"res/level03.png"}
 * ]
 *
 * //load a list of resources
 * cc.LoaderScene.preload(g_mainmenu, this.startGame, this);
 *
 * //load multi lists of resources
 * cc.LoaderScene.preload([g_mainmenu,g_level], this.startGame, this);
 */
cc.LoaderScene.preload = function (resources, selector, target) {
    if (!this._instance) {
        this._instance = new cc.LoaderScene();
        this._instance.init();
    }

    this._instance.initWithResources(resources, selector, target);

    var director = cc.Director.getInstance();
    if (director.getRunningScene()) {
        director.replaceScene(this._instance);
    } else {
        director.runWithScene(this._instance);
    }

    return this._instance;
};
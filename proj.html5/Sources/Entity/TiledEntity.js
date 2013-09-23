/**
 * Tooflya Inc. Development
 *
 * @author Igor Mats from Tooflya Inc.
 * @copyright (c) 2013 by Igor Mats
 *
 * @license http://opensource.org/licenses/gpl-license.php GNU Public License v2
 * @all rights granted under this License are granted for the term of
 * copyright on the Program, and are irrevocable provided the stated
 * conditions are met. This License explicitly affirms your unlimited
 * permission to run the unmodified Program. The output from running a
 * covered work is covered by this License only if the output, given its
 * content, constitutes a covered work. This License acknowledges your
 * rights of fair use or other equivalent, as provided by copyright law.
 *
 * @version
 *
 */

  cc.TiledEntity = cc.Entity.extend({
    init: function(fileName, horizontalFramesCount, verticalFramesCount, parent, callback) {
      this._super(fileName, parent);

      this.m_HorizontalFramesCount = horizontalFramesCount;
      this.m_VerticalFramesCount = verticalFramesCount;

      this.m_FrameWidth = this.m_Width / this.m_HorizontalFramesCount;
      this.m_FrameHeight = this.m_Height / this.m_VerticalFramesCount;

      this.m_FramesCount = this.m_HorizontalFramesCount * this.m_VerticalFramesCount;

      this.m_FramesCoordinatesX = [];
      this.m_FramesCoordinatesY = [];

      var counter = 0;

      for(var i = 0; i < this.m_VerticalFramesCount; i++)
      {
        for(var j = 0; j < this.m_HorizontalFramesCount; j++, counter++)
        {
          this.m_FramesCoordinatesX[counter] = j * (this.m_Width / this.m_HorizontalFramesCount);
          this.m_FramesCoordinatesY[counter] = i * (this.m_Height / this.m_VerticalFramesCount);
        }
      }

      this.setCurrentFrameIndex(0);

      if(callback) {
        callback(this);
      }
    },

    setCurrentFrameIndex: function(index) {
      if(index < this.m_FramesCount && index >= 0)
      {
        if(this.m_CurrentFrameIndex != index) {
          this.setTextureRect(cc.rect(this.m_FramesCoordinatesX[index], this.m_FramesCoordinatesY[index], this.m_Width / this.m_HorizontalFramesCount, this.m_Height / this.m_VerticalFramesCount));

          this.m_CurrentFrameIndex = index;
        }
      }
      else
      {
        console.log("Frame with that index is not found. (" + index + ")");

        this.setCurrentFrameIndex(0);

        this.m_CurrentFrameIndex = 0;
      }
    },
    getCurrentFrameIndex: function() {
      return this.m_CurrentFrameIndex;
    },
    nextFrameIndex: function() {
      var potencialNextFrame = this.getCurrentFrameIndex() + 1;

      this.setCurrentFrameIndex(potencialNextFrame >= this.m_FramesCount ? 0 : potencialNextFrame);
    },
    previousFrameIndex: function() {
      // TODO: Write this method.
    },

    getWidth: function() {
      return this.m_FrameWidth;
    },
    getHeight: function() {
      return this.m_FrameHeight;
    },
    getWidthScaled: function() {
      return this.m_FrameWidth * Math.abs(this.getScaleX());
    },
    getHeightScaled: function() {
      return this.m_FrameHeight * Math.abs(this.getScaleY());
    },

    deepCopy: function() {
      return cc.TiledEntity.create(this.m_TextureFileName, this.m_HorizontalFramesCount, this.m_VerticalFramesCount);
    }
});

cc.TiledEntity.create = function(fileName, horizontalFramesCount, verticalFramesCount, parent, callback) {
  var entity = new cc.TiledEntity();
  entity.init(fileName, horizontalFramesCount, verticalFramesCount, parent, callback);

  return entity;
};
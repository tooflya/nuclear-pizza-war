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

cc.EntityManager = cc.Class.extend({
  init: function(capacity, entity, parent, z, batch) {
    this.m_Elements = [];

    this.m_Parent = parent;
    this.m_LastElementNumber = -1;
    this.m_Capacity = capacity;

    var spriteBatch = cc.SpriteBatchNode.create(entity.m_TextureFileName, this.m_Capacity * (entity.m_Shadow ? 2 : 1));
    spriteBatch.setUserData("cc.SpriteBatchNode");

    for(var i = 0; i < capacity; i++) {
      var currentEntity;

      if(i == 0) {
        currentEntity = entity;
      } else {
        currentEntity = entity.deepCopy();
      }

      currentEntity.setManager(this);
      currentEntity.setID(i);

      if(batch) {
        spriteBatch.addChild(currentEntity, z);
      } else {
        this.m_Parent.addChild(currentEntity, z);
      }

      this.m_Elements[i] = currentEntity;
    }

    if(batch) {
      this.m_Parent.addChild(spriteBatch, z ? z : 0);
    }
  },

  getCount: function() {
    return this.m_LastElementNumber + 1;
  },
  getCapacity: function() {
    return this.m_Capacity;
  },

  create: function() {
    if(++this.m_LastElementNumber < this.m_Capacity) {
      this.get(this.m_LastElementNumber).create();
    } else {
      console.log("Not found an element in the EntityManager with Capacity is " + this.m_Capacity + " and LastElementNumber is " + this.m_LastElementNumber);
    }
  },

  destroy: function(index) {
    if(this.m_LastElementNumber >= 0)
    {
      this.m_Elements.swap(index, this.m_LastElementNumber);

      this.get(index).setID(index);
      this.get(this.m_LastElementNumber).setID(this.m_LastElementNumber);

      this.m_LastElementNumber--;
    }
  },

  clear: function() {
    for(var i = 0; i < this.getCapacity(); i++)
    {
      this.get(i).destroy();
    }
  },

  get: function(index) {
    return this.m_Elements[index];
  },

  last: function() {
    return this.m_Elements[this.m_LastElementNumber];
  }
});

cc.EntityManager.create = function(capacity, entity, parent, z, batch) {
  if(typeof(batch) == 'undefined') {
    batch = true;
  }

  var manager = new cc.EntityManager();
  manager.init(capacity, entity, parent, z, batch);

  return manager;
};
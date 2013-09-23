var s_Debug = "debug.png";
var s_CyberHippo = "cyborghippo.png";
var s_Mojang = "mojang.png";
var s_GameManuBackground = "splash.png";
var s_GameOverBackground = "game_over.png";
var s_GameWoneBackground = "victory.png";
var s_BackgroundStars = "stars.png";
var s_ButtonStart = "button_start.png";
var s_Platform = "pizza_big.png";
var s_Castle = "artichoke.png";
var s_Personage = "player1_1.png";
var s_Decorations = "decorations.png";
var s_Wall1 = "wall1.png";
var s_Wall2 = "wall2.png";
var s_Wall3 = "wall3.png";
var s_EngineParticles = "engine.png";
var s_Shadow = "shadow.png";
var s_SmallShadow = "smallshadow.png";
var s_LargeShadow = "largeshadow.png";
var s_Slice = "ansjovalienbotslice.png";
var s_PersonageShockwave = "shockwave.png";
var s_EnemyShockwave = "alien_shockwave.png";
var s_Bubble = "bubble.png";
var s_BubbleSplash = "bubble_pop.png";
var s_Bullets = "bullets.png";
var s_BulletsCrash = "bullet_impact.png";
var s_Pickups = "pickups.png";
var s_FollowEnemy = "alien1.png";
var s_CastleEnemy = "alien2.png";
var s_FiredEnemy = "alien3.png";
var s_BigEnemy = "alien4.png";
var s_Explosion = "explosion2.png";
var s_LongExplosion = "explosion3.png";
var s_MineExplosion = "explosion1.png";
var s_MineExplosion = "explosion1.png";
var s_Spider = "spider.png";
var s_Holder1 = "holder1.png";
var s_Holder2 = "holder2.png";
var s_UpgradeIcon = [];
s_UpgradeIcon[0] = "shopicons_fire_damage_level.png";
s_UpgradeIcon[1] = "shopicons_firerate.png";
s_UpgradeIcon[2] = "shopicons_speed.png";
s_UpgradeIcon[3] = "shopicons_regenerate.png";
s_UpgradeIcon[4] = "shopicons_health.png";
s_UpgradeIcon[5] = "shopicons_count.png";
s_UpgradeIcon[6] = "shopicons_nova.png";
s_UpgradeIcon[7] = "shopicons_jetpack.png";
s_UpgradeIcon[8] = "shopicons_base_walls.png";
s_UpgradeIcon[9] = "shopicons_base_shot.png";
s_UpgradeIcon[10] = "shopicons_base_blast.png";
s_UpgradeIcon[11] = "shopicons_base_spider.png";

var s_MainTheme = "Resources/Music/mus_fast02.wav";
var s_PersonageShoot = [];
s_PersonageShoot[0] = "Resources/Sound/shot.wav";
s_PersonageShoot[1] = "Resources/Sound/shot.wav";
s_PersonageShoot[2] = "Resources/Sound/shot2.wav";
s_PersonageShoot[3] = "Resources/Sound/shot2.wav";
var s_EnemyShoot = "Resources/Sound/alienshot.wav";
var s_SliceCreated = "Resources/Sound/slice_approaching.wav";
var s_PersonageStartFlying = "Resources/Sound/player_jetpack.wav";
var s_PersonageShootLand = "Resources/Sound/shot_land.wav";
var s_PersonageFlying = "Resources/Sound/player_accelerating.wav";
var s_PersonageFlyingDamage = "Resources/Sound/jetpack_fail.wav";
var s_BubblePop = "Resources/Sound/pizzaplop.wav";
var s_PickupPop = "Resources/Sound/health.wav";
var s_EnemyDestroy = "Resources/Sound/ai_death.wav";
var s_PersonageDestroy = "Resources/Sound/player_death.wav";
var s_EnemyWarning = "Resources/Sound/alien_warning.wav";
var s_EnemySuicide = "Resources/Sound/alien_suicide.wav";
var s_EnemyVoice = "Resources/Sound/ai_voice.wav";
var s_StartLevel = "Resources/Sound/start_level.wav";
var s_Upgrade= "Resources/Sound/upgrade.wav";
var s_SpiderVoice = "Resources/Sound/spider_talk.wav";
var s_SpiderDestroy = "Resources/Sound/big_explosion.wav";

var s_Font = "Franchise";

var s_WarningLowHealth = "Warning: Low Health";
var s_PrepareForBattle = "Prepare for Battle!";
var s_Wealth = "Wealth:"
var s_UpgradeTextes = [];
s_UpgradeTextes[0] = "Fire Damage: {0}";
s_UpgradeTextes[1] = "Fire Rate: {0}";
s_UpgradeTextes[2] = "Speed: {0}";
s_UpgradeTextes[3] = "Regeneration Rate: {0}";
s_UpgradeTextes[4] = "Max Health: {0}";
s_UpgradeTextes[5] = "Beam Ammo: {0}";
s_UpgradeTextes[6] = "Shockwave Damage: {0}";
s_UpgradeTextes[7] = "Jetpack Power: {0}";
s_UpgradeTextes[8] = "Fortification: {0}";
s_UpgradeTextes[9] = "Tower Blaster: {0}";
s_UpgradeTextes[10] = "Nova Defence: {0}";
s_UpgradeTextes[11] = "Defence Spiders: {0}";

var g_resources = [
    {src: s_Debug},
    {src: s_CyberHippo},
    {src: s_Mojang},
    {src: s_GameManuBackground},
    {src: s_GameOverBackground},
    {src: s_GameWoneBackground},
    {src: s_BackgroundStars},
    {src: s_ButtonStart},
    {src: s_Platform},
    {src: s_Castle},
    {src: s_Personage},
    {src: s_Decorations},
    {src: s_Wall1},
    {src: s_Wall2},
    {src: s_Wall3},
    {src: s_EngineParticles},
    {src: s_Shadow},
    {src: s_SmallShadow},
    {src: s_LargeShadow},
    {src: s_Slice},
    {src: s_PersonageShockwave},
    {src: s_EnemyShockwave},
    {src: s_Bubble},
    {src: s_BubbleSplash},
    {src: s_Bullets},
    {src: s_BulletsCrash},
    {src: s_Pickups},
    {src: s_FollowEnemy},
    {src: s_CastleEnemy},
    {src: s_FiredEnemy},
    {src: s_BigEnemy},
    {src: s_Explosion},
    {src: s_LongExplosion},
    {src: s_MineExplosion},
    {src: s_Spider},
    {src: s_Holder1},
    {src: s_Holder2},
    {src: s_UpgradeIcon[0]},
    {src: s_UpgradeIcon[1]},
    {src: s_UpgradeIcon[2]},
    {src: s_UpgradeIcon[3]},
    {src: s_UpgradeIcon[4]},
    {src: s_UpgradeIcon[5]},
    {src: s_UpgradeIcon[6]},
    {src: s_UpgradeIcon[7]},
    {src: s_UpgradeIcon[8]},
    {src: s_UpgradeIcon[9]},
    {src: s_UpgradeIcon[10]},
    {src: s_UpgradeIcon[11]},

    {src: s_PersonageShoot[0]},
    {src: s_PersonageShoot[2]},
    {src: s_PersonageShoot[3]},
    {src: s_EnemyShoot},
    {src: s_SliceCreated},
    {src: s_PersonageStartFlying},
    {src: s_PersonageShootLand},
    {src: s_PersonageFlying},
    {src: s_PersonageFlyingDamage},
    {src: s_BubblePop},
    {src: s_PickupPop},
    {src: s_EnemyDestroy},
    {src: s_PersonageDestroy},
    {src: s_EnemyWarning},
    {src: s_EnemySuicide},
    {src: s_StartLevel},
    {src: s_EnemyVoice},
    {src: s_SpiderVoice},
    {src: s_SpiderDestroy},
    {src: s_Upgrade}
];
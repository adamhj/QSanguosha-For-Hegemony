-- translation for Standard General Package

return {
	-- 蜀势力
	["#liubei"] = "乱世的枭雄",
	["liubei"] = "刘备",
	["rende"] = "仁德",
	[":rende"] = "出牌阶段，你可以将至少一张手牌交给一名角色，若如此做，当你以此法交给其他角色的手牌首次达到三张或更多时，你回复1点体力。",
	["@rende-give"] = "你可以发动“仁德”",
	["~rende"] = "选择任意数量的手牌→选择一名其他角色→点击确定",

	["#guanyu"] = "美髯公",
	["guanyu"] = "关羽",
	["wusheng"] = "武圣",
	[":wusheng"] = "你可以将一张红色牌当【杀】使用或打出。",

	["#zhangfei"] = "万夫不当",
	["zhangfei"] = "张飞",
	["paoxiao"] = "咆哮",
	[":paoxiao"] = "锁定技，你使用【杀】无次数限制。",
	["paoxiao:armor_nullify"] = "场上有君刘备，你现在可以亮将发动【杀】的无视防具效果。" ,

	["#zhugeliang"] = "迟暮的丞相",
	["zhugeliang"] = "诸葛亮",
	["illustrator:zhugeliang"] = "木美人",
	["guanxing"] = "观星",
	[":guanxing"] = "准备阶段开始时，你可以观看牌堆顶的X张牌（X为全场角色数且至多为5），然后将其中任意数量的牌以任意顺序置于牌堆顶，其余以任意顺序置于牌堆底。",
	["kongcheng"] = "空城",
	[":kongcheng"] = "锁定技，每当你成为【杀】或【决斗】的目标时，若你没有手牌，你取消之。",
	["#GuanxingResult"] = "%from 的“<font color=\"yellow\"><b>观星</b></font>”结果：%arg 上 %arg2 下",
	["$GuanxingTop"] = "置于牌堆顶的牌：%card",
	["$GuanxingBottom"] = "置于牌堆底的牌：%card",

	["#zhaoyun"] = "少年将军",
	["zhaoyun"] = "赵云",
	["longdan"] = "龙胆",
	[":longdan"] = "你可以将一张【杀】当【闪】使用或打出；你可以将一张【闪】当【杀】使用或打出。",

	["#machao"] = "一骑当千",
	["machao"] = "马超",
	["mashu_machao"] = "马术",
	[":mashu_machao"] = "锁定技，你与其他角色的距离-1。",
	["tieji"] = "铁骑",
	[":tieji"] = "每当你使用【杀】指定一名目标角色后，你可以进行判定，若结果为红色，该角色不能使用【闪】响应此次对其结算的此【杀】。",

	["#huangyueying"] = "归隐的杰女",
	["huangyueying"] = "黄月英",
	["illustrator:huangyueying"] = "木美人",
	["jizhi"] = "集智",
	[":jizhi"] = "每当你使用非转化的非延时类锦囊牌时，你可以摸一张牌。",
	["@jizhi-exchange"] = "你可以用一张手牌替换展示的【%arg】",
	["qicai"] = "奇才",
	[":qicai"] = "锁定技，你使用锦囊牌无距离限制。",

	["#huangzhong"] = "老当益壮",
	["huangzhong"] = "黄忠",
	["liegong"] = "烈弓",
	[":liegong"] = "每当你于出牌阶段内使用【杀】指定一名角色为目标后，若该角色的手牌数不小于你的体力值或不大于你的攻击范围，你可以令其不能使用【闪】响应此次对其结算的此【杀】。",
	
	["#weiyan"] = "嗜血的独狼",
	["weiyan"] = "魏延",
	["illustrator:weiyan"] = "SoniaTang",
	["kuanggu"] = "狂骨",
	[":kuanggu"] = "锁定技，每当你对距离1以内的一名角色造成1点伤害后，你回复1点体力。",

	["#pangtong"] = "凤雏",
	["pangtong"] = "庞统",
	["lianhuan"] = "连环",
	[":lianhuan"] = "你可以将一张梅花手牌当【铁索连环】使用或重铸。",
	["niepan"] = "涅槃",
	[":niepan"] = "限定技，当你处于濒死状态时，你可以弃置你区域里所有的牌，然后将武将牌平置并重置副将的武将牌，再摸三张牌，最后将体力值回复至3点。",
	["$NiepanAnimate"] = "image=image/animate/niepan.png",
	["@nirvana"] = "涅槃",

	["#wolong"] = "卧龙",
	["wolong"] = "卧龙诸葛亮",
	["&wolong"] = "诸葛亮",
	["illustrator:wolong"] = "北",
	["bazhen"] = "八阵",
	[":bazhen"] = "锁定技，若你的装备区里没有防具牌，你视为装备着【八卦阵】。",
	["huoji"] = "火计",
	[":huoji"] = "你可以将一张红色手牌当【火攻】使用。",
	["kanpo"] = "看破",
	[":kanpo"] = "你可以将一张黑色手牌当【无懈可击】使用。",

	["#liushan"] = "无为的真命主",
	["liushan"] = "刘禅",
	["illustrator:liushan"] = "LiuHeng",
	["xiangle"] = "享乐",
	[":xiangle"] = "锁定技，每当你成为其他角色使用【杀】的目标时，你令该角色选择是否弃置一张基本牌，若其不如此做或其已死亡，此次对你结算的此【杀】对你无效。",
	["@xiangle-discard"] = "你须再弃置一张基本牌使此【杀】生效",
	["fangquan"] = "放权",
	[":fangquan"] = "你可以跳过出牌阶段，若如此做，此回合结束时，你可以弃置一张手牌并选择一名其他角色，令其获得一个额外的回合。",
	["@fangquan-give"] = "你可以弃置一张手牌令一名其他角色进行一个额外的回合",
	["~fangquan"] = "选择一张手牌→选择一名其他角色→点击确定",
	["#Fangquan"] = "%to 将进行一个额外的回合",

	["#menghuo"] = "南蛮王",
	["menghuo"] = "孟获",
	["illustrator:menghuo"] = "废柴男",
	["huoshou"] = "祸首",
	[":huoshou"] = "锁定技，【南蛮入侵】对你无效；锁定技，每当其他角色使用【南蛮入侵】指定目标后，你将此【南蛮入侵】造成的伤害的来源改为你。",
	["zaiqi"] = "再起",
	[":zaiqi"] = "摸牌阶段开始时，若你已受伤，你可以放弃摸牌，亮出牌堆顶的X张牌（X为你已损失的体力值），然后回复等同于其中红桃牌数量的体力，再将这些红桃牌置入弃牌堆，最后获得其余的牌。",
	["#HuoshouTransfer"] = "%from 的“%arg2”被触发，【<font color=\"yellow\"><b>南蛮入侵</b></font>】的伤害来源改为 %from",

	["#zhurong"] = "野性的女王",
	["zhurong"] = "祝融",
	["illustrator:zhurong"] = "废柴男",
	["juxiang"] = "巨象",
	[":juxiang"] = "锁定技，【南蛮入侵】对你无效；锁定技，每当其他角色使用的【南蛮入侵】因结算完毕而置入弃牌堆时，你获得之。",
	["lieren"] = "烈刃",
	[":lieren"] = "每当你使用【杀】对目标角色造成伤害后，你可以与其拼点。若你赢，你获得其一张牌。",

	["#ganfuren"] = "昭烈皇后",
	["ganfuren"] = "甘夫人",
	["illustrator:ganfuren"] = "琛·美弟奇",
	["shushen"] = "淑慎",
	[":shushen"] = "每当你回复1点体力后，你可以令与你势力相同的一名其他角色摸一张牌。",
	["shushen-invoke"] = "你可以发动“淑慎”<br/> <b>操作提示</b>: 选择一名其他角色→点击确定<br/>",
	["shenzhi"] = "神智",
	[":shenzhi"] = "准备阶段开始时，你可以弃置所有手牌，然后若你以此法弃置的手牌数不小于X（X为你的体力值），你回复1点体力。",

}


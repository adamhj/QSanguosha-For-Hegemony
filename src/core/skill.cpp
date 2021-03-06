#include "skill.h"
#include "settings.h"
#include "engine.h"
#include "player.h"
#include "room.h"
#include "client.h"
#include "standard.h"
#include "scenario.h"
#include "serverplayer.h"

#include <QFile>

Skill::Skill(const QString &name, Frequency frequency)
    : frequency(frequency), limit_mark(QString()), default_choice("no"), relate_to_place(QString()), attached_lord_skill(false)
{
    static QChar lord_symbol('$');

    if (name.endsWith(lord_symbol)) {
        QString copy = name;
        copy.remove(lord_symbol);
        setObjectName(copy);
        lord_skill = true;
    } else {
        setObjectName(name);
        lord_skill = false;
    }
}

bool Skill::isLordSkill() const{
    return lord_skill;
}

bool Skill::isAttachedLordSkill() const{
    return attached_lord_skill;
}

QString Skill::getDescription(bool yellow) const{
    QString des_src = Sanguosha->translate(":" + objectName());
    if (des_src == ":" + objectName())
        return QString();
    foreach (QString skill_type, Sanguosha->getSkillColorMap().keys()) {
        QString to_replace = Sanguosha->translate(skill_type);
        if (to_replace == skill_type) continue;
        QString color_str = Sanguosha->getSkillColor(skill_type).name();
        if (des_src.contains(to_replace))
            des_src.replace(to_replace, QString("<font color=%1><b>%2</b></font>").arg(color_str)
                                                                                  .arg(to_replace));
    }

    for (int i = 0; i < 6; i++) {
        Card::Suit suit = (Card::Suit)i;
        QString str = Card::Suit2String(suit);
        QString to_replace = Sanguosha->translate(str);
        bool red = suit == Card::Heart
                || suit == Card::Diamond
                || suit == Card::NoSuitRed;
        if (to_replace == str) continue;
        if (des_src.contains(to_replace))
            if (red)
                des_src.replace(to_replace, QString("<font color=#FF0000>%1</font>").arg(Sanguosha->translate(str+"_char")));
            else
                des_src.replace(to_replace, QString("<font color=#000000><span style=background-color:white>%1</span></font>").arg(Sanguosha->translate(str+"_char")));
    }
    return QString("<font color=%1>%2</font>").arg(yellow ? "#FFFF33" : "#FF0080").arg(des_src);
}

QString Skill::getNotice(int index) const{
    if (index == -1)
        return Sanguosha->translate("~" + objectName());

    return Sanguosha->translate(QString("~%1%2").arg(objectName()).arg(index));
}

bool Skill::isVisible() const{
    return !objectName().startsWith("#");
}

QString Skill::getDefaultChoice(ServerPlayer *) const{
    return default_choice;
}

int Skill::getEffectIndex(const ServerPlayer *, const Card *) const{
    return -1;
}

void Skill::initMediaSource() {
    sources.clear();
    for (int i = 1; ;i++) {
        QString effect_file = QString("audio/skill/%1%2.ogg").arg(objectName()).arg(QString::number(i));
        if (QFile::exists(effect_file))
            sources << effect_file;
        else
            break;
    }

    if (sources.isEmpty()) {
        QString effect_file = QString("audio/skill/%1.ogg").arg(objectName());
        if (QFile::exists(effect_file))
            sources << effect_file;
    }
}

Skill::Location Skill::getLocation() const{
    return parent() ? Right : Left;
}

void Skill::playAudioEffect(int index) const{
    if (!sources.isEmpty()) {
        if (index == -1)
            index = qrand() % sources.length();
        else
            index--;

        // check length
        QString filename;
        if (index >= 0 && index < sources.length())
            filename = sources.at(index);
        else if (index >= sources.length()) {
            while (index >= sources.length())
                index -= sources.length();
            filename = sources.at(index);
        } else
            filename = sources.first();

        Sanguosha->playAudioEffect(filename);
        if (ClientInstance)
            ClientInstance->setLines(filename);
    }
}

Skill::Frequency Skill::getFrequency() const{
    return frequency;
}

QString Skill::getLimitMark() const{
    return limit_mark;
}

QStringList Skill::getSources() const{
    return sources;
}

QDialog *Skill::getDialog() const{
    return NULL;
}

bool Skill::canPreshow() const{
    if (inherits("TriggerSkill")) {
        const TriggerSkill *triskill = qobject_cast<const TriggerSkill *>(this);
        return triskill->getViewAsSkill() == NULL;
    }

    return false;
}

bool Skill::relateToPlace(bool head) const{
    if (head)
        return relate_to_place == "head";
    else
        return relate_to_place == "deputy";
    return false;
}

ViewAsSkill::ViewAsSkill(const QString &name)
    : Skill(name), response_pattern(QString())
{
}

bool ViewAsSkill::isAvailable(const Player *invoker,
                              CardUseStruct::CardUseReason reason,
                              const QString &pattern) const{
    if (!invoker->ownSkill(objectName()) && !invoker->getAcquiredSkills().contains(objectName()) && !invoker->hasFlag(objectName())) // For Shuangxiong
        return false;
    switch (reason) {
    case CardUseStruct::CARD_USE_REASON_PLAY: return isEnabledAtPlay(invoker);
    case CardUseStruct::CARD_USE_REASON_RESPONSE:
    case CardUseStruct::CARD_USE_REASON_RESPONSE_USE: return isEnabledAtResponse(invoker, pattern);
    default:
            return false;
    }
}

bool ViewAsSkill::isEnabledAtPlay(const Player *) const{
    return response_pattern.isEmpty();
}

bool ViewAsSkill::isEnabledAtResponse(const Player *, const QString &pattern) const{
    if (!response_pattern.isEmpty())
        return pattern == response_pattern;
    return false;
}

bool ViewAsSkill::isEnabledAtNullification(const ServerPlayer *) const{
    return false;
}

const ViewAsSkill *ViewAsSkill::parseViewAsSkill(const Skill *skill) {
    if (skill == NULL) return NULL;
    if (skill->inherits("ViewAsSkill")) {
        const ViewAsSkill *view_as_skill = qobject_cast<const ViewAsSkill *>(skill);
        return view_as_skill;
    }
    if (skill->inherits("TriggerSkill")) {
        const TriggerSkill *trigger_skill = qobject_cast<const TriggerSkill *>(skill);
        Q_ASSERT(trigger_skill != NULL);
        const ViewAsSkill *view_as_skill = trigger_skill->getViewAsSkill();
        if (view_as_skill != NULL) return view_as_skill;
    }
    return NULL;
}

ZeroCardViewAsSkill::ZeroCardViewAsSkill(const QString &name)
    : ViewAsSkill(name)
{
}

const Card *ZeroCardViewAsSkill::viewAs(const QList<const Card *> &cards) const{
    if (cards.isEmpty())
        return viewAs();
    else
        return NULL;
}

bool ZeroCardViewAsSkill::viewFilter(const QList<const Card *> &, const Card *) const{
    return false;
}

OneCardViewAsSkill::OneCardViewAsSkill(const QString &name)
    : ViewAsSkill(name), filter_pattern(QString())
{
}

bool OneCardViewAsSkill::viewFilter(const QList<const Card *> &selected, const Card *to_select) const{
    return selected.isEmpty() && !to_select->hasFlag("using") && viewFilter(to_select);
}

bool OneCardViewAsSkill::viewFilter(const Card *to_select) const{
    if (!inherits("FilterSkill") && !filter_pattern.isEmpty()) {
        QString pat = filter_pattern;
        if (pat.endsWith("!")) {
            if (Self->isJilei(to_select)) return false;
            pat.chop(1);
        }
        ExpPattern pattern(pat);
        return pattern.match(Self, to_select);
    }
    return false;
}

const Card *OneCardViewAsSkill::viewAs(const QList<const Card *> &cards) const{
    if (cards.length() != 1)
        return NULL;
    else
        return viewAs(cards.first());
}

FilterSkill::FilterSkill(const QString &name)
    : OneCardViewAsSkill(name)
{
    frequency = Compulsory;
}

TriggerSkill::TriggerSkill(const QString &name)
    : Skill(name), view_as_skill(NULL), global(false), dynamic_priority(0.0)
{
}

const ViewAsSkill *TriggerSkill::getViewAsSkill() const{
    return view_as_skill;
}

QList<TriggerEvent> TriggerSkill::getTriggerEvents() const{
    return events;
}

int TriggerSkill::getPriority() const{
    return (frequency == Limited) ? 3 : 2;
}

QStringList TriggerSkill::triggerable(const ServerPlayer *target) const{
    if (target != NULL && target->isAlive() && target->hasSkill(objectName()))
        return QStringList(objectName());
    return QStringList();
}

QStringList TriggerSkill::triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &ask_who) const{
    return triggerable(player); //temp way
}

bool TriggerSkill::cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const{
    return true;
}

bool TriggerSkill::effect(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const{
    return false;
}

ScenarioRule::ScenarioRule(Scenario *scenario)
    :TriggerSkill(scenario->objectName())
{
    setParent(scenario);
}

int ScenarioRule::getPriority() const{
    return 0;
}

QStringList ScenarioRule::triggerable(const ServerPlayer *) const{
    return QStringList(objectName());
}

MasochismSkill::MasochismSkill(const QString &name)
    : TriggerSkill(name)
{
    events << Damaged;
}

QStringList MasochismSkill::triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data, ServerPlayer * &ask_who) const {
    return TriggerSkill::triggerable(triggerEvent, room, player, data, ask_who);
}

bool MasochismSkill::cost(TriggerEvent triggerEvent, Room *room, ServerPlayer *player, QVariant &data) const {
    return TriggerSkill::cost(triggerEvent, room, player, data);
}

bool MasochismSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &data) const{
    DamageStruct damage = data.value<DamageStruct>();
    onDamaged(player, damage);

    return false;
}

PhaseChangeSkill::PhaseChangeSkill(const QString &name)
    : TriggerSkill(name)
{
    events << EventPhaseStart;
}

bool PhaseChangeSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &) const{
    return onPhaseChange(player);
}

DrawCardsSkill::DrawCardsSkill(const QString &name)
    : TriggerSkill(name)
{
    events << DrawNCards;
}

bool DrawCardsSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &data) const{
    int n = data.toInt();
    data = getDrawNum(player, n);
    return false;
}

GameStartSkill::GameStartSkill(const QString &name)
    : TriggerSkill(name)
{
    events << GameStart;
}

bool GameStartSkill::effect(TriggerEvent, Room *, ServerPlayer *player, QVariant &) const{
    onGameStart(player);
    return false;
}

BattleArraySkill::BattleArraySkill(const QString &name, const BattleArrayType::ArrayType type)
    : TriggerSkill(name), array_type(type)
{
    if (!inherits("LuaBattleArraySkill")) //extremely dirty hack!!!
        view_as_skill = new ArraySummonSkill(objectName());
}

void BattleArraySkill::summonFriends(ServerPlayer *player) const {
    player->summonFriends(array_type);
}

ArraySummonSkill::ArraySummonSkill(const QString &name)
    : ZeroCardViewAsSkill(name)
{

}

const Card *ArraySummonSkill::viewAs() const {
    QString name = objectName();
    name[0] = name[0].toUpper();
    name += "Summon";
    Card *card = Sanguosha->cloneSkillCard(name);
    card->setShowSkill(objectName());
    return card;
}

using namespace BattleArrayType;
bool ArraySummonSkill::isEnabledAtPlay(const Player *player) const{
    if (player->getAliveSiblings().length() < 3) return false;
    if (player->hasFlag("Global_SummonFailed")) return false;
    const BattleArraySkill *skill = qobject_cast<const BattleArraySkill *>(Sanguosha->getTriggerSkill(objectName()));
    if (skill) {
        ArrayType type = skill->getArrayType();
        switch (type) {
            case Siege: {
                if (player->isFriendWith(player->getNextAlive())
                        && player->isFriendWith(player->getLastAlive()))
                    return false;
                if (!player->isFriendWith(player->getNextAlive()))
                    if (!player->getNextAlive(2)->hasShownOneGeneral())
                        return true;
                if (!player->isFriendWith(player->getLastAlive()))
                    return !player->getLastAlive(2)->hasShownOneGeneral();
            }
            break;
            case Formation: {
                int n = player->aliveCount();
                int asked = n;
                for (int i = 1; i < n; ++ i) {
                    Player *target = player->getNextAlive(i);
                    if (player->isFriendWith(target))
                        continue;
                    else if (!target->hasShownOneGeneral())
                        return true;
                    else {
                        asked = i;
                        break;
                    }
                }
                n -= asked;
                for(int i = 1; i < n; ++ i) {
                    Player *target = player->getLastAlive(i);
                    if (player->isFriendWith(target))
                        continue;
                    else return !target->hasShownOneGeneral();
                }
            }
            break;
        }
    }
    return false;
}

int MaxCardsSkill::getExtra(const Player *) const{
    return 0;
}

int MaxCardsSkill::getFixed(const Player *) const{
    return -1;
}

ProhibitSkill::ProhibitSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
}

DistanceSkill::DistanceSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
}

MaxCardsSkill::MaxCardsSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
}

TargetModSkill::TargetModSkill(const QString &name)
    : Skill(name, Skill::Compulsory)
{
    pattern = "Slash";
}

QString TargetModSkill::getPattern() const{
    return pattern;
}

int TargetModSkill::getResidueNum(const Player *, const Card *) const{
    return 0;
}

int TargetModSkill::getDistanceLimit(const Player *, const Card *) const{
    return 0;
}

int TargetModSkill::getExtraTargetNum(const Player *, const Card *) const{
    return 0;
}

SlashNoDistanceLimitSkill::SlashNoDistanceLimitSkill(const QString &skill_name)
    : TargetModSkill(QString("#%1-slash-ndl").arg(skill_name)), name(skill_name)
{
}

int SlashNoDistanceLimitSkill::getDistanceLimit(const Player *from, const Card *card) const{
    if (from->hasSkill(name) && card->getSkillName() == name)
        return 1000;
    else
        return 0;
}

FakeMoveSkill::FakeMoveSkill(const QString &name)
    : TriggerSkill(QString("#%1-fake-move").arg(name)), name(name)
{
    events << BeforeCardsMove << CardsMoveOneTime;
}

int FakeMoveSkill::getPriority() const{
    return 10;
}

QStringList FakeMoveSkill::triggerable(TriggerEvent, Room *, ServerPlayer *target, QVariant &, ServerPlayer * &ask_who) const{
    return (target != NULL) ? QStringList(objectName()) : QStringList();
}

bool FakeMoveSkill::effect(TriggerEvent, Room *room, ServerPlayer *, QVariant &) const{
    QString flag = QString("%1_InTempMoving").arg(name);

    foreach (ServerPlayer *p, room->getAllPlayers())
        if (p->hasFlag(flag)) return true;

    return false;
}

DetachEffectSkill::DetachEffectSkill(const QString &skillname, const QString &pilename)
    : TriggerSkill(QString("#%1-clear").arg(skillname)), name(skillname), pile_name(pilename)
{
    events << EventLoseSkill;
}

QStringList DetachEffectSkill::triggerable(TriggerEvent triggerEvent, Room *room, ServerPlayer *target, QVariant &data, ServerPlayer * &ask_who) const{
    return (target != NULL) ? QStringList(objectName()) : QStringList();
}

bool DetachEffectSkill::effect(TriggerEvent, Room *room, ServerPlayer *player, QVariant &data) const{
    if (data.toString() == name) {
        if (!pile_name.isEmpty())
            player->clearOnePrivatePile(pile_name);
        else
            onSkillDetached(room, player);
    }
    return false;
}

void DetachEffectSkill::onSkillDetached(Room *, ServerPlayer *) const{
}

WeaponSkill::WeaponSkill(const QString &name)
    : TriggerSkill(name)
{
}

QStringList WeaponSkill::triggerable(const ServerPlayer *target) const{
    if (target == NULL) return QStringList();
    if (target->getMark("Equips_Nullified_to_Yourself") > 0) return QStringList();
    return (target->hasWeapon(objectName())) ? QStringList(objectName()) : QStringList();
}

ArmorSkill::ArmorSkill(const QString &name)
    : TriggerSkill(name)
{
}

QStringList ArmorSkill::triggerable(const ServerPlayer *target) const{
    if (target == NULL || target->getArmor() == NULL)
        return QStringList();
    return (target->hasArmorEffect(objectName())) ? QStringList(objectName()) : QStringList();
}


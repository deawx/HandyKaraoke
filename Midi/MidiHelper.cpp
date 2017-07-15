#include "MidiHelper.h"

MidiHelper::MidiHelper()
{

}

QStringList MidiHelper::GMInstrumentNumberNames()
{
    QStringList gln;
    QStringList gl = GMInstrumentNames();

    for (int i=0; i<gl.count(); i++) {
        QString n = QString::number(i).rightJustified(3, '0');
        n = n + " - " + gl[i];
        gln.append(n);
    }

    return gln;
}

QStringList MidiHelper::drumKitNumberNames()
{
    QStringList dln;
    QStringList dl = drumKitNames();


    for (int i=0; i<dl.count(); i++) {
        QString n = QString::number(i).rightJustified(3, '0');
        n = n + " - " + dl[i];
        dln.append(n);
    }

    return dln;
}

QStringList MidiHelper::snareNumberName()
{
    QStringList sl;
    sl.append("38 - " + snareName()[0]);
    sl.append("40 - " + snareName()[1]);
    return sl;
}

QStringList MidiHelper::GMInstrumentNames()
{
    QStringList gmList;
    gmList << "Acoustic Grand Piano" <<
        "Bright Acoustic Piano" <<
        "Electric Grand Piano" <<
        "Honky-tonk Piano" <<
        "Electric Piano 1" <<
        "Electric Piano 2" <<
        "Harpsichord" <<
        "Clavi" <<
        "Celesta" <<
        "Glockenspiel" <<
        "Music Box" <<
        "Vibraphone" <<
        "Marimba" <<
        "Xylophone" <<
        "Tubular Bells" <<
        "Dulcimer" <<
        "Drawbar Organ" <<
        "Percussive Organ" <<
        "Rock Organ" <<
        "Church Organ" <<
        "Reed Organ" <<
        "Accordion" <<
        "Harmonica" <<
        "Tango Accordion" <<
        "Acoustic Guitar (nylon)" <<
        "Acoustic Guitar (steel)" <<
        "Electric Guitar (jazz)" <<
        "Electric Guitar (clean)" <<
        "Electric Guitar (muted)" <<
        "Overdriven Guitar" <<
        "Distortion Guitar" <<
        "Guitar harmonics" <<
        "Acoustic Bass" <<
        "Electric Bass (finger)" <<
        "Electric Bass (pick)" <<
        "Fretless Bass" <<
        "Slap Bass 1" <<
        "Slap Bass 2" <<
        "Synth Bass 1" <<
        "Synth Bass 2" <<
        "Violin" <<
        "Viola" <<
        "Cello" <<
        "Contrabass" <<
        "Tremolo Strings" <<
        "Pizzicato Strings" <<
        "Orchestral Harp" <<
        "Timpani" <<
        "String Ensemble 1" <<
        "String Ensemble 2" <<
        "SynthStrings 1" <<
        "SynthStrings 2" <<
        "Choir Aahs" <<
        "Voice Oohs" <<
        "Synth Voice" <<
        "Orchestra Hit" <<
        "Trumpet" <<
        "Trombone" <<
        "Tuba" <<
        "Muted Trumpet" <<
        "French Horn" <<
        "Brass Section" <<
        "SynthBrass 1" <<
        "SynthBrass 2" <<
        "Soprano Sax" <<
        "Alto Sax" <<
        "Tenor Sax" <<
        "Baritone Sax" <<
        "Oboe" <<
        "English Horn" <<
        "Bassoon" <<
        "Clarinet" <<
        "Piccolo" <<
        "Flute" <<
        "Recorder" <<
        "Pan Flute" <<
        "Blown Bottle" <<
        "Shakuhachi" <<
        "Whistle" <<
        "Ocarina" <<
        "Lead 1 (square)" <<
        "Lead 2 (sawtooth)" <<
        "Lead 3 (calliope)" <<
        "Lead 4 (chiff)" <<
        "Lead 5 (charang)" <<
        "Lead 6 (voice)" <<
        "Lead 7 (fifths)" <<
        "Lead 8 (bass + lead)" <<
        "Pad 1 (new age)" <<
        "Pad 2 (warm)" <<
        "Pad 3 (polysynth)" <<
        "Pad 4 (choir)" <<
        "Pad 5 (bowed)" <<
        "Pad 6 (metallic)" <<
        "Pad 7 (halo)" <<
        "Pad 8 (sweep)" <<
        "FX 1 (rain)" <<
        "FX 2 (soundtrack)" <<
        "FX 3 (crystal)" <<
        "FX 4 (atmosphere)" <<
        "FX 5 (brightness)" <<
        "FX 6 (goblins)" <<
        "FX 7 (echoes)" <<
        "FX 8 (sci-fi)" <<
        "Sitar" <<
        "Banjo" <<
        "Shamisen" <<
        "Koto" <<
        "Kalimba" <<
        "Bag pipe" <<
        "Fiddle" <<
        "Shanai" <<
        "Tinkle Bell" <<
        "Agogo" <<
        "Steel Drums" <<
        "Woodblock" <<
        "Taiko Drum" <<
        "Melodic Tom" <<
        "Synth Drum" <<
        "Reverse Cymbal" <<
        "Guitar Fret Noise" <<
        "Breath Noise" <<
        "Seashore" <<
        "Bird Tweet" <<
        "Telephone Ring" <<
        "Helicopter" <<
        "Applause" <<
        "Gunshot";

    return gmList;
}

QStringList MidiHelper::drumKitNames()
{
    QStringList dList;

    for (int i=0; i<128; i++) {
        switch (i) {
        case 0:
            dList << "Standard";
            break;
        case 8:
            dList << "Room";
            break;
        case 16:
            dList << "Power";
            break;
        case 24:
            dList << "Electronic";
            break;
        case 25:
            dList << "TR-808";
            break;
        case 32:
            dList << "Jazz";
            break;
        case 40:
            dList << "Brush";
            break;
        case 48:
            dList << "Orchestra";
            break;
        case 56:
            dList << "Sound FX";
            break;
        default:
            dList << "Drum Kit";
            break;
        }
    }

    return dList;
}

QStringList MidiHelper::snareName()
{
    QStringList slist;
    slist.append("Acoustic Snare");
    slist.append("Electric Snare");
    return slist;
}

QStringList MidiHelper::instrumentGroupNames()
{
    QStringList gn;

    gn << "Piano" << "Chromatic Percussion" << "Organ" << "Guitar" << "Bass"
       << "Strings" << "Ensemble" << "Brass" << "Reed" << "Pipe" << "Synth Lead"
       << "Synth Pad" << "Synth Effects" << "Ethnic" << "Percussive"
       << "Sound effects";

    return gn;
}
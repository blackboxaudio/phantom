/*
  ==============================================================================

    PhantomUtils.h
    Created: 22 Jan 2021 10:22:44
    Author:  Matthew Maxwell

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

//==========================================================================
#ifndef PHANTOM_PARAMS
#define PHANTOM_PARAMS

namespace Consts {
    //==========================================================================
    constexpr char* _AMP_EG_ATK_PARAM_ID = "ampEgAtk";
    constexpr char* _AMP_EG_ATK_PARAM_NAME = "Amp EG Atk";
    constexpr float _AMP_EG_ATK_DEFAULT_VAL = 0.02f;
    constexpr char* _AMP_EG_DEC_PARAM_ID = "ampEgDec";
    constexpr char* _AMP_EG_DEC_PARAM_NAME = "Amp EG Dec";
    constexpr float _AMP_EG_DEC_DEFAULT_VAL = 0.2f;
    constexpr char* _AMP_EG_SUS_PARAM_ID = "ampEgSus";
    constexpr char* _AMP_EG_SUS_PARAM_NAME = "Amp EG Sus";
    constexpr float _AMP_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char* _AMP_EG_REL_PARAM_ID = "ampEgRel";
    constexpr char* _AMP_EG_REL_PARAM_NAME = "Amp EG Rel";
    constexpr float _AMP_EG_REL_DEFAULT_VAL = 0.6f;

    constexpr char* _FLTR_EG_ATK_PARAM_ID = "fltrEgAtk";
    constexpr char* _FLTR_EG_ATK_PARAM_NAME = "Filter EG Atk";
    constexpr float _FLTR_EG_ATK_DEFAULT_VAL = 0.01f;
    constexpr char* _FLTR_EG_DEC_PARAM_ID = "fltrEgDec";
    constexpr char* _FLTR_EG_DEC_PARAM_NAME = "Filter EG Dec";
    constexpr float _FLTR_EG_DEC_DEFAULT_VAL = 0.4f;
    constexpr char* _FLTR_EG_SUS_PARAM_ID = "fltrEgSus";
    constexpr char* _FLTR_EG_SUS_PARAM_NAME = "Filter EG Sus";
    constexpr float _FLTR_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char* _FLTR_EG_REL_PARAM_ID = "fltrEgRel";
    constexpr char* _FLTR_EG_REL_PARAM_NAME = "Filter EG Rel";
    constexpr float _FLTR_EG_REL_DEFAULT_VAL = 0.8f;

    constexpr char* _PHASOR_EG_ATK_PARAM_ID = "phaseEgAtk";
    constexpr char* _PHASOR_EG_ATK_PARAM_NAME = "Phase EG Atk";
    constexpr float _PHASOR_EG_ATK_DEFAULT_VAL = 0.1f;
    constexpr char* _PHASOR_EG_DEC_PARAM_ID = "phaseEgDec";
    constexpr char* _PHASOR_EG_DEC_PARAM_NAME = "Phase EG Dec";
    constexpr float _PHASOR_EG_DEC_DEFAULT_VAL = 0.25f;
    constexpr char* _PHASOR_EG_SUS_PARAM_ID = "phaseEgSus";
    constexpr char* _PHASOR_EG_SUS_PARAM_NAME = "Phase EG Sus";
    constexpr float _PHASOR_EG_SUS_DEFAULT_VAL = -30.0f;
    constexpr char* _PHASOR_EG_REL_PARAM_ID = "phaseEgRel";
    constexpr char* _PHASOR_EG_REL_PARAM_NAME = "Phase EG Rel";
    constexpr float _PHASOR_EG_REL_DEFAULT_VAL = 1.2f;

    constexpr char* _MOD_EG_ATK_PARAM_ID = "modEgAtk";
    constexpr char* _MOD_EG_ATK_PARAM_NAME = "Mod EG Atk";
    constexpr float _MOD_EG_ATK_DEFAULT_VAL = 0.01f;
    constexpr char* _MOD_EG_DEC_PARAM_ID = "modEgDec";
    constexpr char* _MOD_EG_DEC_PARAM_NAME = "Mod EG Dec";
    constexpr float _MOD_EG_DEC_DEFAULT_VAL = 0.15f;
    constexpr char* _MOD_EG_SUS_PARAM_ID = "modEgSus";
    constexpr char* _MOD_EG_SUS_PARAM_NAME = "Mod EG Sus";
    constexpr float _MOD_EG_SUS_DEFAULT_VAL = -60.0f;
    constexpr char* _MOD_EG_REL_PARAM_ID = "modEgRel";
    constexpr char* _MOD_EG_REL_PARAM_NAME = "Mod EG Rel";
    constexpr float _MOD_EG_REL_DEFAULT_VAL = 0.2f;

    constexpr char* _LFO_RATE_PARAM_ID = "lfoRate";
    constexpr char* _LFO_RATE_PARAM_NAME = "LFO Rate";
    constexpr float _LFO_RATE_DEFAULT_VAL = 20.0f;
    constexpr char* _LFO_SHAPE_PARAM_ID = "lfoShape";
    constexpr char* _LFO_SHAPE_PARAM_NAME = "LFO Shape";
    constexpr float _LFO_SHAPE_DEFAULT_VAL = 0.0f;

    constexpr char* _OSC_RANGE_PARAM_ID = "oscRange";
    constexpr char* _OSC_RANGE_PARAM_NAME = "Osc Range";
    constexpr float _OSC_RANGE_DEFAULT_VAL = 2.0f;
    constexpr char* _OSC_COARSE_TUNE_PARAM_ID = "oscCoarseTune";
    constexpr char* _OSC_COARSE_TUNE_PARAM_NAME = "Osc Coarse Tune";
    constexpr float _OSC_COARSE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char* _OSC_FINE_TUNE_PARAM_ID = "oscFineTune";
    constexpr char* _OSC_FINE_TUNE_PARAM_NAME = "Osc Fine Tune";
    constexpr float _OSC_FINE_TUNE_DEFAULT_VAL = 0.0f;
    constexpr char* _OSC_MOD_DEPTH_PARAM_ID = "oscModDepth";
    constexpr char* _OSC_MOD_DEPTH_PARAM_NAME = "Osc Mod Depth";
    constexpr float _OSC_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char* _OSC_MOD_MODE_PARAM_ID = "oscModMode";
    constexpr char* _OSC_MOD_MODE_PARAM_NAME = "Osc Mod Mode";
    constexpr float _OSC_MOD_MODE_DEFAULT_VAL = 0.0f;
    constexpr char* _OSC_SHAPE_INT_PARAM_ID = "oscShapeInt";
    constexpr char* _OSC_SHAPE_INT_PARAM_NAME = "Osc Shape Int";
    constexpr float _OSC_SHAPE_INT_DEFAULT_VAL = 0.0f;

    constexpr char* _PHASOR_SHAPE_PARAM_ID = "phasorShape";
    constexpr char* _PHASOR_SHAPE_PARAM_NAME = "Phasor Shape";
    constexpr float _PHASOR_SHAPE_DEFAULT_VAL = 0.0f;
    constexpr char* _PHASOR_EG_INT_PARAM_ID = "phasorEgInt";
    constexpr char* _PHASOR_EG_INT_PARAM_NAME = "Phasor EG Int";
    constexpr float _PHASOR_EG_INT_DEFAULT_VAL = 1.0f;
    constexpr char* _PHASOR_LFO_INT_PARAM_ID = "phasorLfoInt";
    constexpr char* _PHASOR_LFO_INT_PARAM_NAME = "Phasor LFO Int";
    constexpr float _PHASOR_LFO_INT_DEFAULT_VAL = 0.0f;

    constexpr char* _FLTR_CUTOFF_PARAM_ID = "filterCutoff";
    constexpr char* _FLTR_CUTOFF_PARAM_NAME = "Filter Cutoff";
    constexpr float _FLTR_CUTOFF_DEFAULT_VAL = 1000.0f;
    constexpr char* _FLTR_RESO_PARAM_ID = "filterReso";
    constexpr char* _FLTR_RESO_PARAM_NAME = "Filter Resonance";
    constexpr float _FLTR_RESO_DEFAULT_VAL = 0.70710678;
    constexpr char* _FLTR_DRIVE_PARAM_ID = "filterDrive";
    constexpr char* _FLTR_DRIVE_PARAM_NAME = "Filter Drive";
    constexpr float _FLTR_DRIVE_DEFAULT_VAL = 0.0f;
    constexpr char* _FLTR_EG_MOD_DEPTH_PARAM_ID = "filterEgModDepth";
    constexpr char* _FLTR_EG_MOD_DEPTH_PARAM_NAME = "Filter EG Mod Depth";
    constexpr float _FLTR_EG_MOD_DEPTH_DEFAULT_VAL = 0.0f;
    constexpr char* _FLTR_LFO_MOD_DEPTH_PARAM_ID = "filterLfoModDepth";
    constexpr char* _FLTR_LFO_MOD_DEPTH_PARAM_NAME = "Filter LFO Mod Depth";
    constexpr float _FLTR_LFO_MOD_DEPTH_DEFAULT_VAL = 0.0f;

    constexpr char* _LEVEL_PARAM_ID = "level";
    constexpr char* _LEVEL_PARAM_NAME = "Level";
    constexpr float _LEVEL_DEFAULT_VAL = 0.0f;

    //==========================================================================
    constexpr int _WAVETABLE_SIZE = 1 << 11;
}

#endif

//===========================================================================
#ifndef EG_TYPE_ENUM
#define EG_TYPE_ENUM

enum EnvelopeGeneratorType {
    AMP = 0,
    FLTR = 1,
    PHASE = 2,
    MOD = 3
};

#endif

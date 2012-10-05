/**
   MiracleGrue - Model Generator for toolpathing. <http://www.grue.makerbot.com>
   Copyright (C) 2011 Far McKon <Far@makerbot.com>, Hugo Boyer (hugo@makerbot.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define GRUE_VERSION  "v0.0.4.0"
#define GRUE_PROGRAM_NAME  "Miracle-Grue"

#include <sstream>
#include <vector>
#include <string>

#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <json/writer.h>

#include "mgl.h"
#include <limits>

namespace mgl {

class ConfigException : public Exception {
public:

    ConfigException(const char *msg) : Exception(msg) {
    }
};

// checks that the value exist before returning it
double doubleCheck(const Json::Value &value, const char *name);
double doubleCheck(const Json::Value &value, const char *name,
        const double defaultVal);
unsigned int uintCheck(const Json::Value &value, const char *name);
unsigned int uintCheck(const Json::Value &value, const char *name,
        const unsigned int defaultVal);
std::string stringCheck(const Json::Value &value, const char *name);
std::string pathCheck(const Json::Value &value, const char *name,
        const std::string &defaultval);
std::string pathCheck(const Json::Value &value, const char *name);
bool boolCheck(const Json::Value &value, const char *name, bool defaultval);
bool boolCheck(const Json::Value &value, const char *name);
//
// This class contains settings for the 3D printer, and user preferences
//

class Configuration {
    std::string filename;
public:
    Json::Value root;

public:
    //	Json::Value &readJsonValue() {return root;}
public:
    /// standard constructor
    Configuration();
    /// standard constructor for loading configuration from a json file
    //    Configuration(std::string& srcFilename);
    /// standard  destructor

    ~Configuration();

    void readFromFile(const char* filename);

    void readFromFile(const std::string &filename) {
        readFromFile(filename.c_str());
    };

    void readFromDefault() {
        readFromFile(defaultFilename());
    };


public:

    bool isMember(const char* key) {
        return this->root.isMember(key);
    }

    /// index function, to read/write values as config["foo"]

    Json::Value& operator[] (const char* key) {

        //     		if(filename.length() ==0)
        //     		{
        //     			ConfigException mixup("Configuration file has not been read");
        //     		    throw mixup;
        //     		}

        //     		if( !root.isMember(key) )
        //     		{
        //     			std::stringstream ss;
        //     			ss << "Can't find \"" << key << "\" in " << filename;
        //     			ConfigException mixup(ss.str().c_str());
        //     			throw mixup;
        //     		}
        return this->root[key];
    }

    const Json::Value& operator[] (const char* key) const {
        return this->root[key];
    }

    std::string asJson(Json::StyledWriter writer = Json::StyledWriter()) const;

private:
    std::string defaultFilename();
};

class GCoderConfig;
class SlicerConfig;
class RegionerConfig;
class ExtruderConfig;
class PatherConfig;

class Extruder;
class Extrusion;

////master configuration object
class GrueConfig {
public:
    GrueConfig();
    void loadFromFile(const Configuration& config);
    Scalar segmentVolume(const Extruder& extruder, const Extrusion& extrusion, 
            const libthing::LineSegment2& segment, Scalar h, Scalar w) const;
private:
    static const Scalar INVALID_SCALAR;// = std::numeric_limits<Scalar>::min();
    static const unsigned int INVALID_UINT = -1;
    static const bool INVALID_BOOL = false;
    
    void loadRaftParams(const Configuration& config);
    void loadSupportParams(const Configuration& config);
    void loadPathingParams(const Configuration& config);
    void loadGantryParams(const Configuration& config);
    void loadProfileParams(const Configuration& config);
    void loadGcodeParams(const Configuration& config);
    void loadSlicingParams(const Configuration& config);
    
    /* This is called from loadProfileParams */
    void loadExtruderParams(const Configuration& config);
    void loadExtrusionParams(const Configuration& config);
    /* --END-- */
    
    //gcoder stuff
    std::map<std::string, Extrusion> extrusionProfiles;
    std::vector<Extruder> extruders;
    
    unsigned int defaultExtruder;
    std::string header;
    std::string footer;
    bool doOutlines;
    bool doInsets;
    bool doInfills;
    bool doFanCommand;
    unsigned int fanLayer;
    bool doPrintLayerMessages;
    bool doPrintProgress;
    //slicer stuff
    Scalar layerH;
    Scalar firstLayerZ;
    //regioner stuff
    Scalar infillDensity;
    unsigned int nbOfShells;
    Scalar layerWidthRatio;
    Scalar insetDistanceMultiplier;
    unsigned int roofLayerCount;
    unsigned int floorLayerCount;
    //raft
    bool doRaft;
    unsigned int raftLayers;
    Scalar raftBaseThickness;
    Scalar raftInterfaceThickness;
    Scalar raftOutset;
    Scalar raftModelSpacing;
    Scalar raftDensity;
    //support
    bool doSupport;
    Scalar supportMargin;
    Scalar supportDensity;
    //pather
    bool doGraphOptimization;
    Scalar coarseness;
    Scalar directionWeight;
    //gcoder gantry
    Scalar rapidMoveFeedRateXY;
    Scalar rapidMoveFeedRateZ;
    bool useEaxis;
    Scalar scalingFactor;
    Scalar startingX;
    Scalar startingY;
    Scalar startingZ;
    Scalar startingA;
    Scalar startingB;
    Scalar startingFeed;
    
};

void loadGCoderConfigFromFile(const Configuration& conf,
        GCoderConfig &gcoder);
void loadSlicerConfigFromFile(const Configuration &config,
        SlicerConfig &slicer);
void loadExtruderConfigFromFile(const Configuration &config,
        ExtruderConfig &extruderCfg);
void loadRegionerConfigFromFile(const Configuration& config,
        RegionerConfig& regionerCfg);
void loadPatherConfigFromFile(const Configuration& config,
        PatherConfig& patherCfg);

}
#endif /* CONFIGURATION_H_ */

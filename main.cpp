
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

int main()
{
    
    QFile geoJsonFile("lat_lon_lines.geojson");
    if(!geoJsonFile.open(QIODevice::WriteOnly | QIODevice::Text)){

        qWarning() << "Faild to open file for writing" ;
        return 1 ;

    }

    QJsonObject geoJson ;
    geoJson["type"] =   "FeatureCollection" ;
    geoJson["name"]=    "geo"               ;

    QJsonObject crs ;
    crs["type"]="name";

    QJsonObject properties ;
    properties["name"] = "urn:ogc:def:crs:OGC:1.3:CRS84" ;
    crs["properties"] = properties ;
    geoJson["crs"]=crs;

    QJsonArray features ;

    for(int lat = -180 ;lat <= 180 ;lat+=2){
        for(int lon = -90 ; lon <= 90 ; lon++){

            QJsonObject feature ;
            QJsonObject properties ;
            QJsonObject geometry ;
            QJsonArray coordinates ;

            feature["type"] = "Feature" ;
            feature["properties"] = properties ;
            geometry["type"] = "LineString" ;
            coordinates.append(QJsonArray({-lat,lon})) ;
            coordinates.append(QJsonArray({lat,lon})) ;

            geometry["coordinates"] = coordinates ;
            feature["geometry"] = geometry ;

            features.append(feature);

        }
    }

    for(int lat = -180 ; lat <= 180 ; lat+=2){
        for(int lon = -90 ; lon <= 90 ; lon++){
            QJsonObject feature ;
            QJsonObject properties ;
            QJsonObject geometry ;
            QJsonArray coordinates ;

            feature["type"] = "Feature" ;
            feature["properties"] = properties ;
            geometry["type"] = "LineString" ;
            coordinates.append(QJsonArray({lat,lon}));
            coordinates.append(QJsonArray({lat,-lon})) ;
            geometry["coordinates"] = coordinates ;
            feature["geometry"] = geometry ;

            features.append(feature) ;

        }


    }

    geoJson["features"] = features ;

    QJsonDocument jsonDoc(geoJson) ;
    geoJsonFile.write(jsonDoc.toJson());
    geoJsonFile.close();

    qDebug() << "GeoJson file has been generated successfully" ;
    return 0 ;


    

}

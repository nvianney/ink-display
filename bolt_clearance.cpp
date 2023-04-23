#include "bolt_clearance.h"

template<typename T>
std::vector<std::vector<T> > arrToVector(T *data, int rows, int cols) {
    std::vector<std::vector<T> > vec;
    for (int r = 0; r < rows; r++) {
        std::vector<T> row;
        for (int c = 0; c < cols; c++) {
            row.push_back(data[r * cols + c]);
        }
        vec.push_back(row);
    }

    return vec;
}

BoltClearance::BoltClearance(int width, int height) : Screen(width, height) {
  
    float weights[4] = {0.25, 0.25, 0.25, 0.25};

    String imperialData[] = {
        "Bolt Size", "Normal Fit", "Close Fit", "Loose Fit",
        "#0",   "0.076",  "0.067",  "3/32",
        "#1",   "0.089",  "0.081",  "0.104",
        "#2",   "0.102",  "3/32",   "0.116",
        "#3",   "0.116",  "0.106",  "0.128",
        "#4",   "0.128",  "0.120",  "0.144",
        "#5",   "5/32",   "9/64",   "11/64",
        "#6",   "0.170",  "0.154",  "0.185",
        "#8",   "0.196",  "0.180",  "0.213",
        "#10",  "0.221",  "0.206",  "0.238",
        "1/4",  "9/32",   "17/64",  "19/64",
        "5/16", "11/32",  "21/64",  "23/64",
        "3/8",  "13/32",  "25/64",  "27/64",
        "7/16", "15/32",  "29/64",  "31/64",
        "1/2",  "9/16",   "17/32",  "39/64",
        "5/8",  "11/16",  "21/32",  "47/64",
        "3/4",  "13/16",  "25/32",  "29/32"
    };

    itProperties.rows = 16;
    itProperties.cols = 4;
    itProperties.width = 350;
    itProperties.height = 400;
    itProperties.weights = (float*) malloc(sizeof(float) * 4);
    memcpy(itProperties.weights, weights, sizeof(float) * 4);
    imperialTable = new Table(itProperties);
    std::vector< std::vector<String> > impVec = arrToVector(imperialData, itProperties.rows + 1, itProperties.cols);
    imperialTable->setHeader(impVec[0]);
    for (int i = 0; i < itProperties.rows; i++) {
        imperialTable->addRow(impVec[i+1]);
    }

    String metricData[] = {
        "Bolt Size", "Normal Fit", "Close Fit", "Loose Fit",
        "M1.6", "1.8",  "1.7",  "2.0",
        "M2",   "2.4",  "2.2",  "2.6",
        "M2.5", "2.9",  "2.7",   "3.1",
        "M3",   "3.4",  "3.2",  "3.6",
        "M4",   "4.5",  "4.3",  "4.8",
        "M5",   "5.5",   "5.3",   "5.8",
        "M6",   "6.6",  "6.4",  "7.0",
        "M8",   "9.0",  "8.4",  "10.0",
        "M10",  "11.0",  "10.5",  "12.0",
        "M12",  "13.5",   "13.0",  "14.5",
        "M14",  "15.5",  "15.0",  "16.5"
    };
    mtProperties.rows = 11;
    mtProperties.cols = 4;
    mtProperties.width = 350;
    mtProperties.height = 286;
    mtProperties.weights = (float*) malloc(sizeof(float) * 4);
    memcpy(mtProperties.weights, weights, sizeof(float) * 4);
    metricTable = new Table(mtProperties);
    std::vector< std::vector<String> > metVec = arrToVector(metricData, mtProperties.rows + 1, mtProperties.cols);
    metricTable->setHeader(metVec[0]);
    for (int i = 0; i < mtProperties.rows; i++) {
        metricTable->addRow(metVec[i+1]);
    }

}

BoltClearance::~BoltClearance() {
    free(imperialTable);
    free(itProperties.weights);
    free(metricTable);
    free(mtProperties.weights);
}

String BoltClearance::getTitle() {
    return "Clearance Hole Diameter";
}

void BoltClearance::update(float delta) {

}

void BoltClearance::draw(Renderer *renderer) {
    imperialTable->draw(renderer, 50, 100);
    metricTable->draw(renderer, 880-50-350, 100);
}

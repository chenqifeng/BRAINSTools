#ifndef BRAINSCutApplyModel_h
#define BRAINSCutApplyModel_h

#include "BRAINSCutPrimary.h"
#include "FeatureInputVector.h"

typedef itk::Image<unsigned char, DIMENSION> BinaryImageType;
typedef BinaryImageType::Pointer             BinaryImagePointer;

class BRAINSCutApplyModel : public BRAINSCutPrimary
{
public:
  BRAINSCutApplyModel( ){};
  BRAINSCutApplyModel( std::string netConfigurationFilename);

  void SetApplyDataSetFromNetConfiguration();

  void Apply();

  void ApplyOnSubject( DataSet& subject);

  void SetANNModelFilenameFromNetConfiguration();

  void ReadANNModelFile();

  BinaryImagePointer PostProcessingOfANNContinuousImage( std::string continuousFilname, 
                                                         scalarType threshold);

  void SetANNOutputThresholdFromNetConfiguration();

  BinaryImagePointer ThresholdImageAtLower( WorkingImagePointer image, scalarType thresholdValue );
  BinaryImagePointer ExtractLabel( BinaryImagePointer image, unsigned char thresholdValue );
  BinaryImagePointer GetOneConnectedRegion( BinaryImagePointer image );

  BinaryImagePointer FillHole( BinaryImagePointer mask);

private:
  NetConfiguration::ApplyDataSetListType applyDataSetList;

  bool        normalization;
  std::string ANNModelFilename;

  scalarType annOutputThreshold;

  OpenCVMLPType * openCVANN;

  /* inline functions */

  inline void PredictROI( InputVectorMapType& roiInputFeatureVector, PredictValueMapType& resultOutputVector,
                          const unsigned int roiNumber,
                          const unsigned int inputVectorSize);

  inline scalarType * GetArrayFromVector( scalarType array[], InputVectorType & vector, unsigned int inputVectorSize);
  inline void         GetOpenCVMatrixFromArray( matrixType & matrix, scalarType array[], unsigned int inputVectorSize);
  inline void WritePredictROIProbabilityBasedOnReferenceImage( const PredictValueMapType& predictedOutput,
                                                               const WorkingImagePointer& referenceImage,
                                                               const WorkingImagePointer& roi,
                                                               const std::string imageFIlename );

  inline std::string GetSubjectOutputDirectory( DataSet& subject);

  inline std::string GetContinuousPredictionFilename( DataSet& subject, std::string currentROIName);

  inline std::string GetOutputROIFilename( DataSet& subject, std::string currentROIName);

};

#endif
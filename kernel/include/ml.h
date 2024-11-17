#ifndef __ML_H
#define __ML_H
#define SUCCESS 0
#define ERROR 1
#include <types.h>
#include <error.h>

typedef void *(*MLMalloc)(size_t);
typedef void *(*MLFree)(void *);

/**
 * @brief 标量
 *
 */
typedef float Scalar;

/**
 * @brief 张量定义
 *
 */
typedef struct _ML_Tensor
{
    /**
     * @brief 数据
     *
     */
    Scalar *data;
    /**
     * @brief 每个维度的大小
     *
     */
    size_t *dims;
    /**
     * @brief 总共有几维
     *
     */
    size_t ndim;
} ML_Tensor;
typedef struct _ML_Context
{
    /* data */
    MLMalloc malloc;
    MLFree free;
} ML_Context;


typedef struct _MLCreateArgs
{
    MLMalloc malloc;
    MLFree free;
} MLCreateArgs;

/**
 * @brief Create context for further machine learning inference.
 * 
 * @param args 
 * @param poutput 
 * @return error_t 
 */
error_t ML_Create(MLCreateArgs args, ML_Context* poutput);
/**
 * @brief 
 * 
 * @param context 
 * @param dims 
 * @param ndim 
 * @param poutput 
 * @return error_t 
 */
error_t ML_CreateZeroTensor(ML_Context* context, size_t *dims, size_t ndim, ML_Tensor* poutput);
error_t ML_FreeTensor(ML_Context* context,ML_Tensor** tensor);
error_t ML_ReLU(ML_Context* context, ML_Tensor* input, ML_Context** output);
Scalar ML_F_ReLU(Scalar scalar);
error_t ML_Mul(ML_Context* context,ML_Tensor a,ML_Tensor b, ML_Context** output);
#endif 6
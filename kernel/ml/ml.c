#include <ml.h>
#include <mos/mm.h>
// #include <emmintrin.h>
// #include <omp.h>
Scalar ML_F_ReLU(Scalar x)
{
    return x > 0 ? x : 0;
}
size_t tensor_length2(size_t *dims, size_t ndim)
{
    if (ndim == 0)
    {
        return 0;
    }
    size_t result = 1;
    for (size_t i = 0; i < ndim; i++)
    {
        result *= dims[i];
    }
    return result;
}
size_t tensor_length(ML_Tensor tensor)
{
    return tensor_length2(tensor->dims, tensor->ndim);
}

error_t ML_CreateZeroTensor(ML_Context context, size_t *dims, size_t ndim, ML_Tensor *output)
{
    size_t size = tensor_length2(dims, ndim);
    Scalar *data = (Scalar *)context->malloc(size * sizeof(Scalar));
    ML_Tensor tensor = (ML_Tensor)context->malloc(sizeof(ML_RTensor));
    size_t dimsSize = sizeof(ndim * sizeof(size_t));
    size_t *_dims = context->malloc(dimsSize);
    memcopy(dims, dimsSize, _dims);
    tensor->data = data;
    tensor->dims = _dims;
    tensor->ndim = ndim;
    *output = tensor;
    return F_OK;
}
error_t ML_CreateZeroTensorWithSameShape(ML_Context context, ML_Tensor sourceTensor, ML_Tensor *output)
{
    return ML_CreateZeroTensor(context, sourceTensor->dims, sourceTensor->ndim, output);
}

error_t ML_FreeTensor(ML_Context context, ML_Tensor tensor)
{
    context->free(tensor->data);
    context->free(tensor->dims);
    context->free(tensor);
    return F_OK;
}

error_t ML_Mul_TensorNum(ML_Context context, ML_Tensor tensor, size_t size, Scalar y, ML_Tensor *output)
{
    size_t max = tensor_length(tensor);
    Scalar *arr = tensor->data;

    ML_CreateZeroTensorWithSameShape(context, tensor, output);

    Scalar *x = tensor->data;
    Scalar *z = (*output)->data;

    for (size_t i = 0; i < max; i++)
    {
        z[i] = x[i] * y;
    }

    return F_OK;
}
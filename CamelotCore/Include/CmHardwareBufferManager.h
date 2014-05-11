#pragma once

#include "CmPrerequisites.h"
#include "CmModule.h"
#include "CmVertexBuffer.h"
#include "CmIndexBuffer.h"
#include "CmVertexDeclaration.h"
#include "CmGpuParamBlock.h"

namespace BansheeEngine 
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup RenderSystem
	*  @{
	*/

	/** Base definition of a hardware buffer manager.
	*/
	class CM_EXPORT HardwareBufferManager : public Module<HardwareBufferManager>
	{
    public:
        HardwareBufferManager();
        virtual ~HardwareBufferManager();
		/** Create a hardware vertex buffer.
        @remarks
            This method creates a new vertex buffer; this will act as a source of geometry
            data for rendering objects. Note that because the meaning of the contents of
            the vertex buffer depends on the usage, this method does not specify a
            vertex format; the user of this buffer can actually insert whatever data 
            they wish, in any format. However, in order to use this with a RenderOperation,
            the data in this vertex buffer will have to be associated with a semantic element
            of the rendering pipeline, e.g. a position, or texture coordinates. This is done 
            using the VertexDeclaration class, which itself contains VertexElement structures
            referring to the source data.
        @remarks Note that because vertex buffers can be shared, they are reference
            counted so you do not need to worry about destroying themm this will be done
            automatically.
        @param vertexSize The size in bytes of each vertex in this buffer; you must calculate
            this based on the kind of data you expect to populate this buffer with.
        @param numVerts The number of vertices in this buffer.
        @param usage One or more members of the HardwareBuffer::Usage enumeration; you are
            strongly advised to use HBU_STATIC_WRITE_ONLY wherever possible, if you need to 
            update regularly, consider HBU_DYNAMIC_WRITE_ONLY and useShadowBuffer=true.
		@param streamOut Whether the vertex buffer will be used for steam out operations of the
			geometry shader.
        */
		virtual VertexBufferPtr 
            createVertexBuffer(UINT32 vertexSize, UINT32 numVerts, GpuBufferUsage usage, bool streamOut = false);

		/** Create a hardware index buffer.
        @remarks Note that because buffers can be shared, they are reference
            counted so you do not need to worry about destroying them this will be done
            automatically.
		@param itype The type in index, either 16- or 32-bit, depending on how many vertices
			you need to be able to address
		@param numIndexes The number of indexes in the buffer
        @param usage One or more members of the HardwareBuffer::Usage enumeration.
        */
		virtual IndexBufferPtr 
            createIndexBuffer(IndexBuffer::IndexType itype, UINT32 numIndexes, GpuBufferUsage usage);

		/**
		 * @brief	Creates an GPU parameter block that you can use for setting parameters
		 * 			for GPU programs.
		 *
		 * @return	The new GPU parameter block.
		 */
		virtual GpuParamBlockBufferPtr createGpuParamBlockBuffer(UINT32 size, GpuParamBlockUsage usage = GPBU_DYNAMIC);

		/**
		 * @brief	Creates a generic buffer that can be passed as a parameter to a shader.
		 *
		 * @param	elementCount  	Number of elements in the buffer. 
		 * @param	elementSize   	Size of each individual element in the buffer, in bytes.
		 * @param	type		  	Type of the buffer.
		 * @param	usage		  	Determines how will the buffer be used.
		 * @param	randomGpuWrite	(optional) Allows the GPU to write to the resource.
		 * @param	useCounter	  	(optional) Binds a counter that can be used from a shader to the buffer.
		 *
		 * Be aware that some of these settings cannot be used together, and you will receive an assert if in debug mode.
		 */
		virtual GpuBufferPtr createGpuBuffer(UINT32 elementCount, UINT32 elementSize, 
			GpuBufferType type, GpuBufferUsage usage, bool randomGpuWrite = false, bool useCounter = false);

        /** Creates a new vertex declaration. */
		virtual VertexDeclarationPtr createVertexDeclaration(const VertexDeclaration::VertexElementList& elements);

	protected:
		virtual VertexDeclarationPtr createVertexDeclarationImpl(const VertexDeclaration::VertexElementList& elements);
		virtual VertexBufferPtr createVertexBufferImpl(UINT32 vertexSize, UINT32 numVerts, GpuBufferUsage usage, bool streamOut = false) = 0;
		virtual IndexBufferPtr createIndexBufferImpl(IndexBuffer::IndexType itype, UINT32 numIndexes, GpuBufferUsage usage) = 0;
		virtual GpuParamBlockBufferPtr createGpuParamBlockBufferImpl() = 0;
		virtual GpuBufferPtr createGpuBufferImpl(UINT32 elementCount, UINT32 elementSize, GpuBufferType type, GpuBufferUsage usage, 
			bool randomGpuWrite = false, bool useCounter = false) = 0;
	};
}


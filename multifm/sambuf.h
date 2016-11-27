#pragma once

#include <multifm/types.h>

#include <tsl/cal.h>
#include <tsl/result.h>

#include <stdint.h>

struct demod_thread;

/**
 * A sample buffer. Represents a count of samples, with the specified
 * integer format.
 *
 * If samples are real, they are packed one after the other.
 *   RRRRRRRRRRRRRR... etc.
 *
 * However, for complex samples, I and Q are interleaved directly:
 *   IQIQIQIQIQIQIQ... etc.
 */
struct sample_buf {
    /**
     * Reference count for this sample buf. This is decremented atomically, and cannot
     * be incremented after being initially set. Sample buffers can be freed in any
     * context.
     */
    uint32_t refcount CAL_ALIGN(16);

    /**
     * The type of a sample in this buffer.
     */
    enum sample_type sample_type;

    /**
     * The number of samples in this sample buffer
     */
    uint32_t nr_samples;

    /**
     * The size of the sample buffer, in bytes
     */
    uint32_t sample_buf_bytes;

    /**
     * The start timestamp (in sample time) of this buffer
     */
    uint64_t start_time_ns;

    /**
     * The actual data. This will need to be cast appropriately.
     */
    uint8_t data_buf[];
};

aresult_t sample_buf_decref(struct demod_thread *thr, struct sample_buf *buf);


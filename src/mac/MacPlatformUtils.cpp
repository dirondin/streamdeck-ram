#include "MacPlatformUtils.h"

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>
#include <sys/sysctl.h>

MemInfo MacPlatformUtils::GetTotalRamUsage()
{
    uint64_t total_mem = 0;
    size_t size = sizeof(total_mem);
    sysctlbyname("hw.memsize", &total_mem, &size, nullptr, 0);

    vm_size_t page_size;
    vm_statistics64_data_t vm_stats;

    const mach_port_t mach_port = mach_host_self();
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO64, (host_info64_t)&vm_stats, &count))
    {
        const uint64_t free_memory = static_cast<uint64_t>(vm_stats.free_count) * static_cast<uint64_t>(page_size);
        const uint64_t used_memory_with_cache = static_cast<uint64_t>(vm_stats.active_count + vm_stats.inactive_count + vm_stats.wire_count + vm_stats.compressor_page_count) * static_cast<uint64_t>(page_size);
        const uint64_t used_memory = static_cast<uint64_t>(vm_stats.internal_page_count - vm_stats.purgeable_count + vm_stats.wire_count + vm_stats.compressor_page_count) * static_cast<uint64_t>(page_size);
        return MemInfo{total_mem, used_memory};
    }

    return MemInfo{0, 0};
}
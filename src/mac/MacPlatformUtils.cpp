#include "MacPlatformUtils.h"

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

uint32_t MacPlatformUtils::GetTotalRamUsage()
{
    vm_size_t page_size;
    vm_statistics64_data_t vm_stats;

    const mach_port_t mach_port = mach_host_self();
    mach_msg_type_number_t count = sizeof(vm_stats) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO, (host_info64_t)&vm_stats, &count))
    {
        const uint64_t free_memory = static_cast<uint64_t>(vm_stats.free_count) * static_cast<uint64_t>(page_size);
        const uint64_t used_memory = (static_cast<uint64_t>(vm_stats.active_count) +
                                      static_cast<uint64_t>(vm_stats.inactive_count) +
                                      static_cast<uint64_t>(vm_stats.wire_count)) *
                                     static_cast<uint64_t>(page_size);
        const uint32_t usage = used_memory * 100 / (used_memory + free_memory);
        return usage;
    }

    return 0;
}
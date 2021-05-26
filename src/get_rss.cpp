//
// Created by Paul Ross on 26/05/2021.
//
#include <iomanip>

#include "get_rss.h"
#include "save_stream_state.h"


// For information: https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-runtime-using-c
// This gives the link: http://nadeausoftware.com/articles/2012/07/c_c_tip_how_get_process_resident_set_size_physical_memory_use
// However that no longer exists.
// Archive link: https://web.archive.org/web/20190923225212/http://nadeausoftware.com/articles/2012/07/c_c_tip_how_get_process_resident_set_size_physical_memory_use
// This code is reformatted from that code, lightly edited, added header file etc.

/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */

#if defined(_WIN32)
#include <windows.h>
    #include <psapi.h>
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/resource.h>
/* Added for faster (?) Mac OS X RSS value in getCurrentRSS_alternate. */
#include <libproc.h>
#if defined(__APPLE__) && defined(__MACH__)
#include <mach/mach.h>
#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
#include <fcntl.h>
        #include <procfs.h>
    #elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
        #include <stdio.h>
#endif
#else
#error "Cannot define getPeakRSS( ) or getCurrentRSS( ) for an unknown OS."
#endif

/**
 * Returns the peak (maximum so far) resident set size (physical
 * memory use) measured in bytes, or zero if the value cannot be
 * determined on this OS.
 */
size_t getPeakRSS(void) {
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (size_t)info.PeakWorkingSetSize;
#elif (defined(_AIX) || defined(__TOS__AIX__)) || (defined(__sun__) || defined(__sun) || defined(sun) && (defined(__SVR4) || defined(__svr4__)))
    /* AIX and Solaris ------------------------------------------ */
    struct psinfo psinfo;
    int fd = -1;
    if ( (fd = open( "/proc/self/psinfo", O_RDONLY )) == -1 )
        return (size_t)0L;      /* Can't open? */
    if ( read( fd, &psinfo, sizeof(psinfo) ) != sizeof(psinfo) )
    {
        close( fd );
        return (size_t)0L;      /* Can't read? */
    }
    close( fd );
    return (size_t)(psinfo.pr_rssize * 1024L);
#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
    /* BSD, Linux, and OSX -------------------------------------- */
    struct rusage rusage;
    getrusage( RUSAGE_SELF, &rusage );
#if defined(__APPLE__) && defined(__MACH__)
    return (size_t)rusage.ru_maxrss;
#else
    return (size_t)(rusage.ru_maxrss * 1024L);
#endif

#else
    /* Unknown OS ----------------------------------------------- */
    return (size_t)0L;          /* Unsupported. */
#endif
}

/**
 * Returns the current resident set size (physical memory use) measured
 * in bytes, or zero if the value cannot be determined on this OS.
 */
size_t getCurrentRSS(void) {
#if defined(_WIN32)
    /* Windows -------------------------------------------------- */
    PROCESS_MEMORY_COUNTERS info;
    GetProcessMemoryInfo( GetCurrentProcess( ), &info, sizeof(info) );
    return (size_t)info.WorkingSetSize;
#elif defined(__APPLE__) && defined(__MACH__)
    /* OSX ------------------------------------------------------ */
    struct mach_task_basic_info info;
    mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
    if ( task_info( mach_task_self( ), MACH_TASK_BASIC_INFO,
                    (task_info_t)&info, &infoCount ) != KERN_SUCCESS )
        return (size_t)0L;      /* Can't access? */
    return (size_t)info.resident_size;
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
    /* Linux ---------------------------------------------------- */
    long rss = 0L;
    FILE* fp = NULL;
    if ( (fp = fopen( "/proc/self/statm", "r" )) == NULL )
        return (size_t)0L;      /* Can't open? */
    if ( fscanf( fp, "%*s%ld", &rss ) != 1 ) {
        fclose( fp );
        return (size_t)0L;      /* Can't read? */
    }
    fclose( fp );
    return (size_t)rss * (size_t)sysconf( _SC_PAGESIZE);
#else
    /* AIX, BSD, Solaris, and Unknown OS ------------------------ */
    return (size_t)0L;          /* Unsupported. */
#endif
}

size_t getCurrentRSS_alternate(void) {
#if defined(__APPLE__)
    /* OSX ------------------------------------------------------ */
    /* Empty fields in struct. */
    /*
    struct rusage rusage;
    getrusage( RUSAGE_SELF, &rusage );
    return (size_t)(rusage.ru_ixrss + rusage.ru_idrss + rusage.ru_isrss);
     */
    /*
     * This works though.
     * Could use PROC_PID_RUSAGE ?
     */
    pid_t pid = getpid();
    struct proc_taskinfo proc;
    int st = proc_pidinfo(pid, PROC_PIDTASKINFO, 0, &proc, PROC_PIDTASKINFO_SIZE);
    if (st == 0) {
        return 0;
    }
    return proc.pti_resident_size;
#endif
    return getCurrentRSS();
}

const double MEGABYTES = (1 << 20);

double getPeakRSSMb() { return getPeakRSS() / MEGABYTES; }
double getCurrentRSSMb() { return getCurrentRSS() / MEGABYTES; }
double getCurrentRSS_alternateMb() { return getCurrentRSS_alternate() / MEGABYTES; }

//static const int MB_PRECISION = 6;
//static const int MB_WIDTH = 14;
static const int MB_PRECISION = 3;
static const int MB_WIDTH = 10;

#define RSS_SNAPSHOT_REPORT_PAGES 0

#if RSS_SNAPSHOT_REPORT_PAGES
std::ostream &operator<<(std::ostream &os, const RSSSnapshot &rss) {
    StreamFormatState stream_state(os); // Preserve state
    os << "RSS(pages):";
    os << " was: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_initial_pages();
    os << " now: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_now_pages();
    os << " diff: " << std::setw(MB_WIDTH) << std::showpos << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_now_diff_pages() << std::noshowpos;
    os << " Peak was: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_peak_initial_pages();
    os << " now: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_peak_now_pages();
    os << " diff: " << std::setw(MB_WIDTH) << std::showpos << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_peak_diff_pages() << std::noshowpos;
    os << " " << rss.name();
    return os;
}
#else
std::ostream &operator<<(std::ostream &os, const RSSSnapshot &rss) {
    StreamFormatState stream_state(os); // Preserve state
    os << "RSS(Mb):";
    os << " was: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_initial_mb();
    os << " now: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_now_mb();
    os << " diff: " << std::setw(MB_WIDTH) << std::showpos << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_now_diff_mb() << std::noshowpos;
    os << " Peak was: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_peak_initial_mb();
    os << " now: " << std::setw(MB_WIDTH) << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_peak_now_mb();
    os << " diff: " << std::setw(MB_WIDTH) << std::showpos << std::fixed << std::setprecision(MB_PRECISION);
    os << rss.rss_peak_diff_mb() << std::noshowpos;
    os << " " << rss.name();
    return os;
}
#endif

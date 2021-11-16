//
// Created by Paul Ross on 26/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_GET_RSS_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_GET_RSS_H

#include <iostream>

#include <stdlib.h>

/**
 * Return the peak RSS in bytes.
 * @return
 */
size_t getPeakRSS();
/**
 * Return the current RSS in bytes.
 * @return
 */
size_t getCurrentRSS();
/**
 * Return the current RSS in bytes.
 * @return
 */
size_t getCurrentRSS_alternate();

/**
 * Size of one megabyte in bytes, 1 << 20
 */
extern const double MEGABYTES;

//double getPeakRSSMb();
//double getCurrentRSSMb();
//double getCurrentRSS_alternateMb();


/**
 * Class that takes a snapshot of RSS usage.
 */
class RSSSnapshot {
private:
    const double MEGABYTE = 1 << 20;
    const size_t PAGE_SIZE = 4096;
public:
    RSSSnapshot(const std::string name) : m_name(name), m_rss_initial(getCurrentRSS()),
                                          m_rss_peak_initial(getPeakRSS()) {}

    const std::string &name() const { return m_name; }

    double rss_initial_mb() const { return m_rss_initial / MEGABYTE; }

    double rss_peak_initial_mb() const { return m_rss_peak_initial / MEGABYTE; }

    double rss_now_mb() const { return getCurrentRSS() / MEGABYTE; }

    double rss_peak_now_mb() const { return getPeakRSS() / MEGABYTE; }

    double rss_now_diff_mb() const {
        return (static_cast<double>(getCurrentRSS()) - static_cast<double>(m_rss_initial)) / MEGABYTE;
    }

    double rss_peak_diff_mb() const {
        return (static_cast<double>(getPeakRSS()) - static_cast<double>(m_rss_peak_initial)) / MEGABYTE;
    }

    size_t rss_initial_pages() const { return m_rss_initial / PAGE_SIZE; }

    size_t rss_peak_initial_pages() const { return m_rss_peak_initial / PAGE_SIZE; }

    size_t rss_now_pages() const { return getCurrentRSS() / PAGE_SIZE; }

    size_t rss_peak_now_pages() const { return getPeakRSS() / PAGE_SIZE; }

    long rss_now_diff_pages() const {
        return (static_cast<long>(getCurrentRSS()) - static_cast<long>(m_rss_initial)) / PAGE_SIZE;
    }

    long rss_peak_diff_pages() const {
        return (static_cast<long>(getPeakRSS()) - static_cast<long>(m_rss_peak_initial)) / PAGE_SIZE;
    }

protected:
    std::string m_name;
    size_t m_rss_initial;
    size_t m_rss_peak_initial;
};

std::ostream &operator<<(std::ostream &os, const RSSSnapshot &rss);

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_GET_RSS_H

//------------------------------------------------------
#include "stdafx.h"
#include "dtraceroute.h"

#include "common/Common.h"
#include "common/CommonOperations.h"
#include "common/ParseReply.h"

#include <json/json.h>

#include <algorithm>

using namespace std;

//------------------------------------------------------

ApplicationStats*	g_pApplicationStats = nullptr;

//------------------------------------------------------

ApplicationStats::ApplicationStats(const string& sTarget_) : sTarget(sTarget_)
{
	g_pApplicationStats = this;
}

//------------------------------------------------------

ApplicationStats::~ApplicationStats()
{
	g_pApplicationStats = nullptr;
}

//------------------------------------------------------

void ApplicationStats::Print()
{
}

//------------------------------------------------------

int MakePackOfJobsByCountry(const string& sCountryCode, const string& sTarget, const ApplicationOptions& options, ProbeApiRequester& requester, ApplicationStats& stats)
{
	const auto nRestJobs = options.nCount - stats.nSent;
	const auto nDesiredProbeCount = nRestJobs;
	const auto nRequestedProbeCount = nDesiredProbeCount > 10 ? nDesiredProbeCount : 10;

	const string sUrl = OSSFMT("StartTracertTestByCountry?countrycode=" << sCountryCode
		<< "&destination=" << sTarget
		<< "&probeslimit=" << nRequestedProbeCount
		<< "&ttl=" << options.nTTL
		<< "&timeout=" << options.nMaxTimeoutMs);

	ProbeApiRequester::Request request(sUrl);
	request.nHttpTimeoutSec += options.nMaxTimeoutMs / 1000;

	const ProbeApiRequester::Reply reply = requester.DoRequest(request, options.bDebug);
	if (!reply.bSucceeded)
	{
		cerr << "ERROR! " << reply.sErrorDescription << endl;
		return eRetCode::ApiFailure;
	}

	using namespace ProbeAPI;
	vector<ProbeInfo> items;

	try
	{
		items = ParseTracertTestByCountryResult(reply.sBody);
	}
	catch (exception& e)
	{
		cerr << "ERROR! " << e.what() << endl;
		return eRetCode::ApiFailure;
	}

	bool bFirstIteration = true;
	for (const auto& info : items)
	{
		size_t iHop = 0;
		for (const auto& hop : info.tracert.vectHops)
		{
			// Tracing route to google-public-dns-a.google.com [8.8.8.8]
			// over a maximum of 30 hops:
			//   1    <1 ms    <1 ms    <1 ms  10.10.0.1
			//   2     3 ms     3 ms     4 ms  124.47.118.1
			//   3     *        *        *     124.47.118.100
			cout << setw(3) << ++iHop;
			for (const auto& ping : hop.vectResults)
			{
				const int nWidth = 5;
				DoSleep(ping, bFirstIteration);

				if (ping.bTimeout)
				{
					cout << " " << setw(nWidth - 1) << " " << "*" << "   ";
				}
				else if (ping.nTimeMs < 1)
				{
					cout << " " << setw(nWidth - 2) << " " << "<1" << " ms";
				}
				else
				{
					cout << " " << setw(nWidth) << ping.nTimeMs << " ms";
				}
			}
			cout << "  " << hop.sReplyHost << endl;
		}

		cout << endl;
		cout << "Trace complete." << endl;
		cout << endl;
	}

	// hack to have only one call to this function:
	stats.nSent = options.nCount;

	return eRetCode::OK;
}

//------------------------------------------------------

int DoByCountry(const ApplicationOptions& options)
{
	int res = eRetCode::OK;

	const string& sTarget = options.sTarget;

	cout << endl;
	cout << "Tracing route to [" << sTarget << "]";
	cout << flush;

	ProbeApiRequester requester;

	string sCountryCode = options.sModeArgument;
	if (DEFAULT_COUNTRY_META == sCountryCode)
	{
		const CommonOptions options2(options.bDebug, options.sModeArgument);
		sCountryCode = GetDefaultSourceCountry(requester, options2);
	}

	cout << " from country code " << sCountryCode << ":" << endl;
	cout << "over a maximum of " << options.nTTL << " hops:" << endl;
	cout << endl;
	cout << flush;

	ApplicationStats stats(sTarget);

	while (stats.nSent < options.nCount)
	{
		const auto nPreviousSend = stats.nSent;

		const int nRes = MakePackOfJobsByCountry(sCountryCode, sTarget, options, requester, stats);
		if (eRetCode::OK != nRes)
		{
			res = nRes;
			break;
		}
		if (nPreviousSend == stats.nSent)
		{
			// don't try again if no results are returned!
			break;
		}
	}

	stats.Print();

	return res;
}

//------------------------------------------------------
#if 0
int MakePackOfJobsByAsn(const string& sAsnId, const string& sTarget, const ProgramOptions& options, ProbeApiRequester& requester, PingingStats& stats)
{
	const auto nRestJobs = options.nPacketCount - stats.nSent;
	const auto nDesiredProbeCount = nRestJobs * 4;
	const auto nRequestedProbeCount = nDesiredProbeCount > 10 ? nDesiredProbeCount : 10;

	// Note! Currently StartPingTestByAsn does not support timeout argument, but I kept it here just in case.
	const string sUrl = OSSFMT("StartPingTestByAsn?asnid=" << sAsnId
		<< "&destination=" << sTarget
		<< "&probeslimit=" << nRequestedProbeCount
		<< "&timeout=" << options.nMaxTimeoutMs);

	ProbeApiRequester::Request request(sUrl);
	request.nHttpTimeoutSec += options.nMaxTimeoutMs / 1000;

	const ProbeApiRequester::Reply reply = requester.DoRequest(request, options.bDebug);
	if (!reply.bSucceeded)
	{
		cerr << "ERROR! " << reply.sErrorDescription << endl;
		return eRetCode::ApiFailure;
	}

	using namespace ProbeAPI;
	vector<ProbeInfo> items;

	try
	{
		items = ParsePingTestByAsnResult(reply.sBody);
	}
	catch (exception& e)
	{
		cerr << "ERROR! " << e.what() << endl;
		return eRetCode::ApiFailure;
	}

	bool bFirstIteration = true;
	for (const auto& info : items)
	{
		// Pinging 8.8.8.8 with 32 bytes of data:
		// Reply from 8.8.8.8: bytes=32 time=13ms TTL=55
		DoSleep(info.ping, bFirstIteration);

		++stats.nSent;
		if (info.bTimeout)
		{
			cout << "Request timed out.";
		}
		else
		{
			++stats.nReceived;
			stats.nPingMin = (min)(stats.nPingMin, info.nTimeMs);
			stats.nPingMax = (max)(stats.nPingMax, info.nTimeMs);
			stats.nPingSum += info.nTimeMs;
			cout << "Reply from " << sTarget << ": bytes=" << options.nPacketSize << " time=" << info.nTimeMs << "ms TTL=" << options.nTTL;
		}

		if (options.bVerbose)
		{
			cout << " to " << info.sUniqueId << " (" << info.network.sName << ")";
		}

		cout << endl;
	}

	return eRetCode::OK;
}
#endif
//------------------------------------------------------

int DoByAsn(const ApplicationOptions& options)
{
	cerr << "ERROR! This function is not implemented!" << endl;
	return eRetCode::NotSupported;
#if 0
	int res = eRetCode::OK;

	const string& sTarget = options.sTarget;
	const string& sAsnId = options.sModeArgument;

	cout << endl;
	cout << "Pinging " << sTarget << " with " << options.nPacketSize << " bytes of data";
	cout << " from " << sAsnId << ":" << endl;
	cout << flush;

	ProbeApiRequester requester;

	PingingStats stats(sTarget);

	while (stats.nSent < options.nPacketCount)
	{
		const auto nPreviousSend = stats.nSent;

		const int nRes = MakePackOfJobsByAsn(sAsnId, sTarget, options, requester, stats);
		if (eRetCode::OK != nRes)
		{
			res = nRes;
			break;
		}
		if (nPreviousSend == stats.nSent)
		{
			// don't try again if no results are returned!
			break;
		}
	}

	stats.Print();

	return res;
#endif
}

//------------------------------------------------------

int Application(const ApplicationOptions& options)
{
	const CommonOptions options2(options.bDebug, options.sModeArgument);

	switch (options.mode)
	{
	case ApplicationOptions::MODE_DO_BY_COUNTRY:
		return DoByCountry(options);
	case ApplicationOptions::MODE_DO_BY_ASN:
		return DoByAsn(options);
	case ApplicationOptions::MODE_GET_COUNTRIES:
		return ListCountries(options2);
	case ApplicationOptions::MODE_GET_ASNS:
		return ListAsns(options2);
	default:
		cerr << "ERROR! Unknown program mode " << options.mode << endl;
		return eRetCode::NotSupported;
	}
}

//------------------------------------------------------

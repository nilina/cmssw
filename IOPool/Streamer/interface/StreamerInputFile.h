#ifndef IOPool_Streamer_StreamerInputFile_h
#define IOPool_Streamer_StreamerInputFile_h

#include "IOPool/Streamer/interface/InitMessage.h"
#include "IOPool/Streamer/interface/EventMessage.h"
#include "IOPool/Streamer/interface/MsgTools.h"
#include "Utilities/StorageFactory/interface/IOTypes.h"
#include "Utilities/StorageFactory/interface/Storage.h"

#include <memory>

#include<string>
#include<vector>

namespace edm {
  class EventSkipperByID;
  class StreamerInputFile {
  public:

    /**Reads a Streamer file */
    explicit StreamerInputFile(std::string const& name,
      std::shared_ptr<EventSkipperByID> eventSkipperByID = std::shared_ptr<EventSkipperByID>());

    /** Multiple Streamer files */
    explicit StreamerInputFile(std::vector<std::string> const& names,
      std::shared_ptr<EventSkipperByID> eventSkipperByID = std::shared_ptr<EventSkipperByID>());

    ~StreamerInputFile();

    bool next(); /** Moves the handler to next Event Record */

    InitMsgView const* startMessage() const { return startMsg_.get(); }
    /** Points to File Start Header/Message */

    EventMsgView const* currentRecord() const { return currentEvMsg_.get(); }
    /** Points to current Record */

    bool newHeader() { bool tmp = newHeader_; newHeader_ = false; return tmp;}  /** Test bit if a new header is encountered */

    /// Needs to be public because of forking.
    void closeStreamerFile();

  private:

    void openStreamerFile(std::string const& name);
    IOSize readBytes(char* buf, IOSize nBytes);
    IOOffset skipBytes(IOSize nBytes);

    void readStartMessage();
    int readEventMessage();

    bool openNextFile();
    /** Compares current File header with the newly opened file header
               Returns false in case of mismatch */
    bool compareHeader();

    void logFileAction(char const* msg);

    std::shared_ptr<InitMsgView> startMsg_;
    std::shared_ptr<EventMsgView> currentEvMsg_;

    std::vector<char> headerBuf_; /** Buffer to store file Header */
    std::vector<char> eventBuf_;  /** Buffer to store Event Data */

    unsigned int currentFile_; /** keeps track of which file is in use at the moment*/
    std::vector<std::string> streamerNames_; /** names of Streamer files */
    bool multiStreams_;  /** True if Multiple Streams are Read */
    std::string currentFileName_;
    bool currentFileOpen_;

    std::shared_ptr<EventSkipperByID> eventSkipperByID_;

    uint32 currRun_;
    uint32 currProto_;

    bool newHeader_;

    std::shared_ptr<Storage> storage_;

    bool endOfFile_;
  };
}

#endif

#ifndef BUILDRESULT_H
#define BUILDRESULT_H

enum BuildResult{
    noStatus = 0,
    success = 1,
    failure = 2,
    aborted = 3,
    unstable = 4,
    end
};

#endif // BUILDRESULT_H

#ifndef ANALYZER_H
#define ANALYZER_H

class Analyzer {
public:
    Analyzer();
    virtual ~Analyzer();

    /**
     * @brief Analyzes the input files.
     * @return 0 in case of success.
     */
    virtual int analyze() = 0;

    /**
     * @brief Add file(s).
     */
    virtual void add_files(std::set<std::string&>&);
    virtual void add_file(const std::string&) = 0;

};

#endif /* ANALYZER_H */

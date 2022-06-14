#include <string>

struct PageHeader {
    std::string              title;
    std::vector<std::string> tags;
};

struct Page {
    PageHeader  header;
    std::string body;
};

struct PageTemplate {
    std::string path;
    std::string template_text;
    PageTemplate(std::string path);
    PageTemplate(std::string path, std::string template_text);
};

std::string render(PageTemplate page_template, Page page);

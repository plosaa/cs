{% assign all_pages = site.pages %}

{% assign cpp_files = "" | split: "," %}
{% for file in site.static_files %}
  {% assign ext = file.path | split: "." | last | downcase %}
  {% if ext == "cpp" %}
    {% assign path = file.path %}
    {% if path contains "/" %}
      {% assign path = path | remove_first: "/" %}
    {% endif %}
    {% assign cpp_files = cpp_files | push: path %}
  {% endif %}
{% endfor %}

{% assign all_pages = all_pages | concat: cpp_files | sort_natural %}

<h1>所有文章</h1>

{% assign categories = "" | split: "," %}
{% assign valid_ext = "md,cpp" | split: "," %}

{% for page in all_pages %}
  {% assign dirs = page.path | split: "/" %}
  {% assign ext = dirs.last | split: "." | last | downcase %}

  {% if valid_ext contains ext and dirs.size > 1 and dirs[0] != "" %}
      {% assign category = dirs[0] %}
      {% unless categories contains category %}
        {% assign categories = categories | push: category %}
      {% endunless %}
  {% endif %}
{% endfor %}

{% for category in categories %}
  <h2>{{ category }}</h2>
  <ul>
    {% assign displayed_files = "" | split: "," %}

    {% for page in all_pages %}

      {% if page.path %}
        {% assign filepath = page.path %}
      {% else %}
        {% assign filepath = page %}
      {% endif %}

      {% assign dirs = filepath | split: "/" %}
      {% assign ext = dirs.last | split: "." | last | downcase %}

      {% if filepath contains category and valid_ext contains ext %}
        {% assign title = filepath %}
        {% assign subpath = filepath %}

        {% assign linkpath = subpath %}

        {% if ext == "md" %}
          {% if dirs.last == "README.md" %}
            {% assign linkpath = subpath | replace: 'README.md', 'index.html' %}
          {% else %}
            {% assign linkpath = subpath | replace: '.md', '.html' %}
          {% endif %}
        {% endif %}

        {% unless displayed_files contains linkpath %}
          {% assign displayed_files = displayed_files | push: linkpath %}
          <li>
            <a href="{{ linkpath }}">{{ linkpath }}</a>
          </li>
        {% endunless %}
      {% endif %}
    {% endfor %}
  </ul>
{% endfor %}

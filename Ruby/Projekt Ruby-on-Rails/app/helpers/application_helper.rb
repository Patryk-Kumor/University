module ApplicationHelper
  def sorting_link(base_path, direction, current_sorting, other_params)
    css_class = if current_sorting == direction
                  'active'
                else
                  ''
                end

    url_params = { sort_by: direction }.merge(other_params)
    url = "#{base_path}?#{url_params.to_query}"
    "<li class='#{css_class}'><a href='#{url}'>#{direction}</a></li>".html_safe
  end
end

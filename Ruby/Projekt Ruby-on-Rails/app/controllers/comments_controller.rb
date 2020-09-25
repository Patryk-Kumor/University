class CommentsController < ApplicationController
  before_action :authenticate_admin_user!, only: %i[destroy undo_report]
  def create
    @comment = Comment.new(params.require(:comment).permit(:content, :product_id).merge(user: current_user))
    flash[:notice] = if @comment.save
                       'Komentarz został dodany'
                     else
                       @comment.errors.full_messages.join('. ')
                     end
    redirect_to @comment.product
  end

  def destroy
    @comment = Comment.find(params[:id])
    @comment.destroy
    redirect_back(fallback_location: root_path)
    flash[:notice] = 'Comment was destroyed!'
  end

  def report
    @comment = Comment.find(params[:id])
    @comment.update review_request: true
    redirect_to @comment.product
    flash[:notice] = 'Comment reported!'
  end

  def undo_report
    @comment = Comment.find(params[:id])
    @comment.update review_request: false
    redirect_to comments_reported_path
    flash[:notice] = 'Request rejected!'
  end

  def reported
    @reported_comments = Comment.where(review_request: true)
    add_breadcrumb 'Reported comments', comments_reported_path
  end

  private

  def set_user_id
    !current_user ? nil : current_user.id
  end
end
